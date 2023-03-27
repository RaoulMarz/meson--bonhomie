#ifndef GAMEINFOLOGGER_H
#define GAMEINFOLOGGER_H

#include <string>
#include "GameState.h"
#include "World.h"
#include "PlayerCommand.h"
//#include "Car.h"
//#include "Command.h"

typedef enum {
    DUMMY = 0,
    SYSTEM_ERROR = 1,
    LOGFILE = 2
} LogSelector;

class GameInfoLogger {
public:
    GameInfoLogger();
    GameInfoLogger(LogSelector selector, std::string logPath);
    GameInfoLogger(const GameInfoLogger& orig);
    virtual ~GameInfoLogger();
    
    void logCommand(GameState gameState, World myWorld, PlayerCommand myCommand);
    //void logComboCommand(GameState gameState, Car car, Command myCommand);
    //void logMessage(GameState gameState, Car car, std::string category, std::string message);
    void logGeneral(GameState gameState, std::string message);
    void logInfo(std::string category, std::string message);
    void setDefaultLogDescriptorIfEmpty();
    void setLogSelector(LogSelector logSelector);
    LogSelector getLogSelector() const;
    void setLogFileDescriptor(std::string logFileDescriptor);
    std::string getLogFileDescriptor() const;
    void setLogFilePath(std::string logFilePath);
    std::string getLogFilePath() const;
    void setEnableLogging(bool enableLogging);
    bool isEnableLogging() const;
private:
    std::string logFilePath;
    std::string logFileDescriptor;
    LogSelector logSelector;
    bool enableLogging = true;
    
    void GameInfoLogger_private(LogSelector selector, std::string logPath);
    void private_writeMessage(std::string logMessage);
};

#endif /* CARINFOLOGGER_H */

