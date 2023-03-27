#include <sstream>
#include <fstream>
#include "extrahelper.h"

static const std::string FileSystemSeparator = "/";

/*
std::string ExtraHelper::printVector2(Vector2 vec, std::string tag) {
    std::stringstream ss;
    ss << tag << vec.x << "," << vec.y << std::endl;
    return ss.str();
}*/

std::string ExtraHelper::getWorkingPath() {
    char workDirChars[2048];
    memset(workDirChars, 0, 2048);
    getcwd(workDirChars, 2047);
    return workDirChars;
}

std::string ExtraHelper::combineFilePath(std::string aPath, std::string aFile) {
    return aPath + FileSystemSeparator + aFile;
}

std::vector<std::string> ExtraHelper::SplitTextOn(std::string mainStr, std::string split, bool includeSplit) {
    std::vector<std::string> res;
    if ( (mainStr.length() > 0) && (mainStr.length() > split.length()) ) {
        std::string workStr = mainStr;
        std::size_t found = 0;
        while ( (found >= 0) && (found < workStr.length()) ) {
            found = workStr.find(split);
            if ( (found >= 0) && (found < workStr.length()) ) {
                std::string foundStr = workStr.substr(0, found);
                workStr = workStr.substr(found + split.length());
                res.push_back(foundStr);
            }
        }
        if (workStr.length() > 0)
            res.push_back(workStr);
    }
    return res;
}

std::vector<std::string> ExtraHelper::readFileAsVector(std::string dataFile) {
    std::vector<std::string> res;
    std::string line;
    std::ifstream infile((const char*) dataFile.c_str(), std::ifstream::in);
    while (getline(infile, line, '\n')) {
        res.push_back(line);
    }
    return res;
}

std::string ExtraHelper::readFileAsString(std::string dataFile) {
    std::string line;
    std::stringstream ss;
    std::ifstream infile((const char*) dataFile.c_str(), std::ifstream::in);
    while (getline(infile, line, '\n')) {
        ss << line << std::endl;
    }
    return ss.str();
}

bool ExtraHelper::writeTextFile(std::string dataFile, std::string text, bool append) {
    bool res = false;
    std::ofstream outFile;
    if (append)
        outFile.open(dataFile, std::ios_base::app);
    else
        outFile.open(dataFile, std::ios_base::out);
    outFile << text;
    outFile.close();
    res = true;
    return res;
}

void ExtraHelper::CopyFile(std::string sourcePath, std::string destinationPath, std::string fileName) {
    std::ifstream src(sourcePath, std::ios::binary);
    std::string destCopyPath = combineFilePath(destinationPath, fileName);
    std::ofstream dst(destCopyPath, std::ios::binary);
    dst << src.rdbuf();
}

std::string ExtraHelper::printShortTimestamp() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[128];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof (buffer), "%d%m%Y#%H%M%S", timeinfo);
    return buffer;
}

int ExtraHelper::GetIntValue(std::string parseText, std::string field) {
    int res = 0;
    auto index = parseText.find(field);
    if ((index >= 0) && (index < parseText.length())) {
        std::string valueTail = parseText.substr(index + field.length() + 1);
        ExtraHelper::trim(valueTail);
        if (valueTail.length() > 1) {
            res = std::stoi(valueTail);
        }
    }
    return res;
}

std::vector<std::string> ExtraHelper::GetVectorListValue(std::string parseText, std::string field) {
    std::vector<std::string> res;
    if ((parseText.length() > 1) && (parseText.length() > field.length())) {
        auto index = parseText.find(field);
        if ((index >= 0) && (index < parseText.length())) {
            std::string valueTail = parseText.substr(index + field.length());
            ExtraHelper::trim(valueTail);
            res = ExtraHelper::SplitTextOn(valueTail, ",", false);
        }
    }
    return res;
}

int ExtraHelper::GetIndexMatchedString(const std::vector<std::string>& vectorStringValues, std::string compare, int indexOffset) {
    int res = indexOffset - 1;
    int index = indexOffset;
    for (std::string strValue : vectorStringValues) {
        if (compare.find(strValue) >= 0) {
            res = index;
            break;
        }
        res += 1;
    }
    return res;
}

