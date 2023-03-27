#include "SignalRHelper.h"
#include "datetime.h"
#include "CalendarDate.h"
#include "GameState.h"
#include "GameConfig.h"
#include "Bot.h"
#include "BotService.hpp"
#include "PlayerCommand.h"
#include "UUID.hpp"
#include "GameInfoLogger.h"
#include "argparse.hpp"
#include "extrahelper.h"
#include "signalrclient/hub_connection.h"
#include "signalrclient/hub_connection_builder.h"
#include "signalrclient/signalr_value.h"

// using namespace argparse;

BotService botService;

/**
 * Logger Functions
 */

void log_game_state()
{
    GameState gameState = botService.getGameState();
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
                   .count();
    std::cout << "Timestamp: " << now << std::endl;
    std::cout << "World: " << std::endl;
    std::cout << "size: " << gameState.world.size << std::endl;
    // std::cout << "Center Point: x: " << gameState.world.centerPoint.x << ", y: " << gameState.world.centerPoint.y
    //           << std::endl;
    // std::cout << "Radius: " << gameState.world.radius << std::endl;
    std::cout << "Game Tick: " << gameState.world.currentTick << std::endl
              << std::endl;

    // std::cout << "Game Objects: " << gameState.gameObjects.size() << std::endl << std::endl;

    Bot bot = botService.getBot();

    std::cout << "Bot: " << bot.id << std::endl;
    // std::cout << "Bot - Speed: " << bot.speed << std::endl;
    // std::cout << "Bot - Heading: " << bot.currentHeading << std::endl;
    // std::cout << "Bot - Size: " << bot.size << std::endl;
    // std::cout << "Bot - x: " << bot.position.x << ", y: " << bot.position.y << std::endl;
    std::cout << "===================================" << std::endl
              << std::endl;
}

void log_player_action(PlayerCommand &playerAction)
{
    std::cout << "PlayerId: " << playerAction.getPlayerID() << ", actions: " <<  playerAction.getActionsPrinted() << std::endl;
}

std::string tokeniseConnectionState(signalr::connection_state connState)
{
    std::string token = "";
    switch (connState)
    {
    case signalr::connection_state::connected:
        token = "Connected";
        break;
    case signalr::connection_state::connecting:
        token = "Connecting";
        break;
    case signalr::connection_state::disconnecting:
        token = "Disconnecting";
        break;
    case signalr::connection_state::disconnected:
        token = "Disconnected";
        break;
    }
    return token;
}

void log_connection_state(signalr::hub_connection &connection)
{
    std::string connState = tokeniseConnectionState(connection.get_connection_state());
    jed_utils::datetime currentTime;
    
    std::cout << "Current Time: " << currentTime.to_string() << std::endl;
    std::cout << "ConState: " << connState << std::endl;
}

/**
 * Handler Functions
 */

void handle_disconnect(std::promise<void> &task)
{
    // Other cleanup here
    std::cout << "Disconnected" << std::endl;
    // End the connection
    task.set_value();
}

void handle_bot_registered(const std::string &id)
{
    std::cout << "Registered: " << id << std::endl;

    botService.setPlayerId(const_cast<std::string &>(id));

    Bot botGameObject;
    Position botPosition;
    botPosition.x = 0;
    botPosition.y = 0;
    // botGameObject.gameObjectType = ObjectTypes::Player;
    // botGameObject.size = 10;
    botGameObject.id = id;
    // botGameObject.position = botPosition;
    botService.setBot(botGameObject);
}

void handle_bot_action(signalr::hub_connection &connection, std::promise<void> &startTask)
{
    try {
        // Compute next action
        botService.computeNextPlayerAction(startTask);
        // Get next action
        std::optional<PlayerCommand> nextAction = botService.getPlayerCommand();
        if (nextAction)
        {
            log_player_action(*nextAction);
            SignalRHelper::send_player_command(connection, *nextAction);
        }
    } catch (const std::exception& e) {
        std::cout << "exception in handle_bot_action: " << e.what() << std::endl;
    }
}

void handle_game_state(const signalr::value &m, signalr::hub_connection &connection, std::promise<void> &startTask, GameInfoLogger &sysLogger)
{
    std::string exceptionMarker;
    try {
        CalendarDate nowDate;        
        std::cout << " Time :: " << nowDate.toString() << std::endl;
        std::cout << "handle_game_state(), m is_map() = " << m.is_map() << std::endl;
        std::cout << "m is_array() = " << m.is_array() << std::endl;
        GameState gameState;

        if (m.is_array())
        {
            auto mapGameState = m.as_array()[0].as_map();
            exceptionMarker = "mapGameState ==> as_map()";
            std::map<std::string, signalr::value> worldMap = mapGameState.find("world")->second.as_map();
            exceptionMarker = "worldMap ==> as_map()";
            std::cout << "handle_game_state(), worldMap.size() = " << worldMap.size() << std::endl;
            sysLogger.logInfo("handle_game_state()", std::string("worldMap.size() = ") + std::to_string(worldMap.size()));
            exceptionMarker = "handle_game_state ==> printing";
            gameState.processJsonMap(mapGameState);
            exceptionMarker = "processJsonMap";
        }

        botService.setGameState(gameState);
        log_game_state();
        exceptionMarker = "log_game_state";
    } catch (const std::exception& e) {
        std::cout << "exception in handle_game_state: " << e.what() << " :: marker = " << exceptionMarker << std::endl;
    }
    //handle_bot_action(connection, startTask);
}

void handle_config_values(const signalr::value &m, signalr::hub_connection &connection, std::promise<void> &startTask, GameInfoLogger &sysLogger)
{
    auto map = m.as_array()[0].as_map();

    std::cout << "handle_config_values(), m is_map() = " << m.is_map() << std::endl;
    std::cout << "m is_array() = " << m.is_array() << std::endl;
    GameConfig gameConfig;

    if (m.is_array())
    {
        auto mapConfig = m.as_array()[0].as_map();
        // std::map<std::string, signalr::value> worldMap = map.find("world")->second.as_map();
        gameConfig.processJsonMap(mapConfig);
    }
}

/**
 * Helper functions
 */
std::string getToken()
{
    const char *token = std::getenv("Token");
    if (token == nullptr)
    {
        return uuid::generate_uuid_v4();
    }
    else
    {
        return token;
    }
}

void processArguments(int argc, char **argv, std::vector<std::string> &res, std::map<std::string, std::string> &argumentFieldValues)
{
    argparse::ArgumentParser parser("Bonhomie arguments");
    parser.add_argument("--version");
    //        .names({"-v", "--version"})
    //.description("version")
    //        .required(false);
    // parser.add_argument()
    //        .names({"-L", "--logpath"})
    //.description("logpath")
    //        .required(false);
    parser.add_argument("--logpath");
    parser.add_argument("--workingpath");
    parser.add_argument("--rounds");

    // parser.enable_help();
    // auto err = parser.parse(argc, (const char**) argv);
    auto unknown_args = parser.parse_known_args(argc, argv);
    // if (err) {
    //     std::cout << err << std::endl;
    //     return;
    // }
    // if (parser.exists("help"))
    if (parser.is_used(std::string("--help")))
    {
        // parser.print_help();
        return;
    }
    if (parser.is_used(std::string("--version")))
    {
        res.push_back("version");
        std::cout << "Version: 0.22\t\tDate: 21/03/2023\n";
        return;
    }
    if (parser.is_used(std::string("--logpath")))
    {
        res.push_back("logpath");
        argumentFieldValues["logpath"] = parser.get<std::string>("--logpath");
    }
    if (parser.is_used(std::string("--workingpath")))
    {
        res.push_back("workingpath");
        argumentFieldValues["workingpath"] = parser.get<std::string>("--workingpath");
    }
    if (parser.is_used(std::string("--rounds")))
    {
        res.push_back("rounds");
        argumentFieldValues["rounds"] = parser.get<std::string>("--rounds");
    }
}

void run()
{
    GameInfoLogger systemLogger(LogSelector::LOGFILE, "bonhomie-logs");
    BotService bService = botService;
    botService.setLogger(systemLogger);
    // Get SignalR Hub Connection
    signalr::hub_connection connection = SignalRHelper::initializeHubConnect();

    // Start Task promise
    std::promise<void> startTask;

    // Disconnected
    connection.on("Disconnect", [&startTask](const signalr::value &m)
                  { handle_disconnect(startTask); });

    // On Bot Register
    connection.on("Registered", [](const signalr::value &m)
                  { handle_bot_registered(m.as_array()[0].as_string()); });

    // On GameState Received
    connection.on("ReceiveBotState", [&](const signalr::value &m)
                  { handle_game_state(m, connection, startTask, systemLogger); });

    connection.on("ReceiveConfigValues", [&](const signalr::value &m)
                  { handle_config_values(m, connection, startTask, systemLogger); });

    // On GameComplete Received
    connection.on("ReceiveGameComplete", [](const signalr::value &m)
                  {
                      // disconnect(startTask);
                  });

    // Start the main connection
    connection.start([&connection, &startTask, &bService](const std::exception_ptr &exception)
                    {
                        if (exception)
                        {
                            try
                            {
                                 std::rethrow_exception(exception);
                            }
                            catch (const std::exception &ex)
                            {
                                 std::cout << "Exception when starting connection: " << ex.what() << std::endl;
                            }
                            handle_disconnect(startTask);
                            return;
                        }
                        std::cout << connection.get_connection_id() << std::endl;

                        std::this_thread::sleep_for(std::chrono::milliseconds(500));

                        // Get initial token
                        std::string token = getToken();
                        std::cout << "Initial Token: " << token << std::endl;
                        std::string nickname = "Bon-Homie";

                         // Send register to Game Runner
                         SignalRHelper::send_register(connection, token, nickname);
                
                        Bot bot = botService.getBot();
                        std::this_thread::sleep_for(std::chrono::milliseconds(200));

                         // Main Bot Loop
                        while (connection.get_connection_state() == signalr::connection_state::connected)
                        {
                            std::string connectionStatus = tokeniseConnectionState(connection.get_connection_state());
                            std::cout << "Connection State: " << connectionStatus << std::endl;
                            std::cout << "Bot info: " << bot.id << std::endl;
                            usleep(25000L);
                            handle_bot_action(connection, startTask);
                        }
                    });
    startTask.get_future().get();

    //Bot bot = botService.getBot();
    // Main Bot Loop
    /*
    while (connection.get_connection_state() == signalr::connection_state::connected)
    {
        std::string connectionStatus = tokeniseConnectionState(connection.get_connection_state());
        std::cout << "Connection State: " << connectionStatus << std::endl;
        std::cout << "Bot info: " << bot.id << std::endl;
        usleep(25000L);
        handle_bot_action(connection, startTask);
    }
    */

    std::promise<void> stopTask;
    connection.stop([&stopTask](std::exception_ptr exception)
                    {
            try
            {
                if (exception)
                {
                    std::rethrow_exception(exception);
                }

                std::cout << "connection stopped successfully" << std::endl;
            }
            catch (const std::exception& e)
            {
                std::cout << "exception when stopping connection: " << e.what() << std::endl;
            }

            stopTask.set_value(); });
    stopTask.get_future().get();
}

int main(int argc, char **argv)
{
    std::vector<std::string> appCommandArguments;
    std::map<std::string, std::string> argumentFieldValues;
    processArguments(argc, argv, appCommandArguments, argumentFieldValues);
    run();
    return 0;
}
