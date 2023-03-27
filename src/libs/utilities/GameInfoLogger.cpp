/* 
 * File:   CarInfoLogger.cpp
 * Author: raoul
 * 
 * Created on 23 April 2020, 6:27 PM
 */

#include <iostream>
#include <sstream>
#include "GameInfoLogger.h"
#include "CalendarDate.h"
#include "extrahelper.h"

GameInfoLogger::GameInfoLogger() {
    this->GameInfoLogger_private(LogSelector::SYSTEM_ERROR, "");
}

GameInfoLogger::GameInfoLogger(LogSelector selector, std::string logPath) {
    logFilePath = logPath;
    logSelector = selector;
}

GameInfoLogger::GameInfoLogger(const GameInfoLogger& orig) {
    logFilePath = orig.logFilePath;
    logSelector = orig.logSelector;
}

GameInfoLogger::~GameInfoLogger() {
}

void GameInfoLogger::GameInfoLogger_private(LogSelector selector, std::string logPath) {
    logFilePath = logPath;
    logSelector = selector;
}

void GameInfoLogger::setDefaultLogDescriptorIfEmpty() {
    if (logFileDescriptor.length() <= 0) {
        logFileDescriptor = "bonhomie-info.log";
    }
}

void GameInfoLogger::private_writeMessage(std::string logMessage) {
    if (!enableLogging)
        return;
    switch (logSelector) {
        case LogSelector::DUMMY: {
            break;
        }
        case LogSelector::LOGFILE: {
            setDefaultLogDescriptorIfEmpty();
            std::string logFile = ExtraHelper::combineFilePath(logFilePath, logFileDescriptor);
            if ( (logFilePath.length() >= 1) && (!ExtraHelper::PathExists(logFilePath) ) ) {
                ExtraHelper::CreatePath(logFilePath);
            }
            ExtraHelper::writeTextFile(logFile, logMessage);
            break;
        }
        case LogSelector::SYSTEM_ERROR: {
            std::cerr << logMessage;
            break;
        }
    }
}

void GameInfoLogger::logCommand(GameState gameState, World myWorld, PlayerCommand myCommand) {
    CalendarDate calendarTimeVal;
    std::stringstream streamOut;
    streamOut << "[" << calendarTimeVal.toString() << "]::" << std::endl;
    /*
    streamOut << "[" << gameState.toString() + "]::");
    streamOut << "<car>=" + car.toString() + "; ");
    streamOut << "<opponent>=" + opponent.toString() + "; ");
    streamOut << "<direction>=" + direction.toString() + "; \n");
     * */
    std::string logMessage = streamOut.str();
    private_writeMessage(logMessage);
}

/*
void CarInfoLogger::logComboCommand(GameState gameState, Car car, Command myCommand) {
    CalendarDate calendarTimeVal;
    std::stringstream streamOut;
    streamOut << "[" << calendarTimeVal.toString() << "]::" << std::endl;
    streamOut << "Gamestate=" << gameState.getCurrentRound() << "," << gameState.getMaxRounds() << std::endl;
    streamOut << "Player Car=" << car.toString() << std::endl;
    std::string logMessage = streamOut.str();
    private_writeMessage(logMessage);
}

void CarInfoLogger::logMessage(GameState gameState, Car car, std::string category, std::string message) {
    CalendarDate calendarTimeVal;
    std::stringstream streamOut;
    streamOut << "[" << calendarTimeVal.toString() << "]::" << std::endl;
    streamOut << "Gamestate=" << gameState.getCurrentRound() << "," << gameState.getMaxRounds() << std::endl;
    streamOut << "Category=" << category << std::endl;
    streamOut << "Message=" << message << std::endl;
    std::string logMessage = streamOut.str();
    private_writeMessage(logMessage);
}
*/

void GameInfoLogger::logGeneral(GameState gameState, std::string message) {
    CalendarDate calendarTimeVal;
    std::stringstream streamOut;
    streamOut << "[" << calendarTimeVal.toString() << "]::" << std::endl;
    //streamOut << "Gamestate=" << gameState.getCurrentRound() << "," << gameState.getMaxRounds() << std::endl;
    streamOut << "Message=" << message << std::endl;
    std::string logMessage = streamOut.str();
    private_writeMessage(logMessage);
}

void GameInfoLogger::logInfo(std::string category, std::string message) {
    CalendarDate calendarTimeVal;
    std::stringstream streamOut;
    streamOut << "[" << calendarTimeVal.toString() << "]::" << std::endl;
    streamOut << "Category=" << category << std::endl;
    streamOut << "Message=" << message << std::endl;
    std::string logMessage = streamOut.str();
    private_writeMessage(logMessage);
}

void GameInfoLogger::setLogSelector(LogSelector logSelector) {
    this->logSelector = logSelector;
}

LogSelector GameInfoLogger::getLogSelector() const {
    return logSelector;
}

void GameInfoLogger::setLogFileDescriptor(std::string logFileDescriptor) {
    this->logFileDescriptor = logFileDescriptor;
}

std::string GameInfoLogger::getLogFileDescriptor() const {
    return logFileDescriptor;
}

void GameInfoLogger::setLogFilePath(std::string logFilePath) {
    this->logFilePath = logFilePath;
}

std::string GameInfoLogger::getLogFilePath() const {
    return logFilePath;
}

void GameInfoLogger::setEnableLogging(bool enableLogging) {
    this->enableLogging = enableLogging;
}

bool GameInfoLogger::isEnableLogging() const {
    return enableLogging;
}