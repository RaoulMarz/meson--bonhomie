#ifndef EXTRA_HELPER_H
#define EXTRA_HELPER_H

//#include <Godot.hpp>
#include <vector>
#include <sstream>
#include <cstring>
#include <algorithm> 
#include <cctype>
#include <locale>
#include <sys/stat.h>
#include <unistd.h>
#include <filesystem>

class ExtraHelper {
public:
    //static std::string printVector2(Vector2 vec, std::string tag = "");
    // trim from start (in place)

    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)

    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)

    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }
    
    static inline bool StringEndsWith(std::string main, std::string sub) {
        bool res = false;
        if ( (main.length() >= 1) && (sub.length() <= main.length()) ) {
            size_t findIdx = main.rfind(sub);
            if (findIdx != std::string::npos) {
                res = findIdx >= (main.length() - sub.length());
            }
        }
        return res;
    }

    static std::vector<std::string> readFileAsVector(std::string dataFile);

    static std::string readFileAsString(std::string dataFile);

    static bool writeTextFile(std::string dataFile, std::string text, bool append = true);

    static std::string getWorkingPath();

    static std::string combineFilePath(std::string aPath, std::string aFile);

    template <typename T>
    static std::string printDebugVector(std::string tag, std::vector<T> vectorList) {
        std::stringstream stringreader;
        for (T item : vectorList) {
            stringreader << item << std::endl;
            //strncat(debugText, stringreader.str().c_str(), stringreader.str().length()  );
        }
        return stringreader.str();
    }

    static std::vector<std::string> SplitTextOn(std::string mainStr, std::string split, bool includeSplit = false);

    static inline bool FileExists(std::string aFile) {
        struct stat buffer;
        return (stat(aFile.c_str(), &buffer) == 0);
    }

    static inline bool PathExists(std::string aPath) {
        struct stat buffer;
        if (stat(aPath.c_str(), &buffer) == 0)
            return S_ISDIR(buffer.st_mode);
        return false;
    }

    static inline void CreatePath(std::string aPath) {
        mkdir(aPath.c_str(), 0777);
        //fs::create_directories(aPath);
    }
    
    static void CopyFile(std::string sourcePath, std::string destinationPath, std::string fileName);

    static inline std::string RemoveIfPathExists(std::string aPath, std::string subPath) {
        std::string res = aPath;
        size_t findIdx = aPath.rfind(subPath);
        if (findIdx != std::string::npos) {
            if (findIdx >= aPath.length() - subPath.length()) {
                res = aPath.substr(0, findIdx - 1);
            }
        }
        return res;
    }

    static inline std::string GetCurrentWorkingDirectory() {
        std::string res = "";
        char buff[FILENAME_MAX]; //create string buffer to hold path
        getcwd(buff, FILENAME_MAX);
        res = buff;
        return res;
    }

    std::string printShortTimestamp();

    static int GetIntValue(std::string parseText, std::string field);

    static std::vector<std::string> GetVectorListValue(std::string parseText, std::string field);

    static int GetIndexMatchedString(const std::vector<std::string>& vectorStringValues, std::string compare, int indexOffset = 0);

};

#endif
