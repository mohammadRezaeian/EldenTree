#include <iostream>
#include <thread>
#include "EventHandler.h"

int main() {
    EventHandler _eventHandler;


    _eventHandler.addGod(WICHGOD::AIR, [](const std::string& action) {
        std::cout << "God Air Received Message: " << action << std::endl;
    });

    _eventHandler.addGod(WICHGOD::WATER, [](const std::string& action) {
        std::cout << "God Water Received Message: " << action << std::endl;
    });

    _eventHandler.addGod(WICHGOD::EARTH, [](const std::string& action) {
        std::cout << "God EARTH Received Message: " << action << std::endl;
    });

    _eventHandler.addGod(WICHGOD::WIND, [](const std::string& action) {
        std::cout << "God WIND Received Message: " << action << std::endl;
    });

    std::thread([&] { _eventHandler.sendMessage(WATER, "Hello from AIR");}).detach();
    std::thread([&] { _eventHandler.sendMessage(AIR, "Hello from WATER");}).detach();
    std::thread([&] { _eventHandler.sendMessage(EARTH, "Hello from WATER");}).detach();
    std::thread([&] { _eventHandler.sendMessage(WIND, "Hello from WATER");}).detach();

        std::cout <<"hello world";

    return 0;
}
