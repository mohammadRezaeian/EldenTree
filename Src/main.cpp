#include <iostream>
#include <thread>
#include "EventHandler.h"
#include <memory>

std::atomic<int> m_done =0; // Flag to indicate when all threads are done

int main() {
    auto _eventHandler = std::make_shared<EventHandler>();  // Shared pointer

    _eventHandler->addGod(WICHGOD::AIR, [](const std::string& action) {
        std::cout << "God Air Received Message: " << action << std::endl;
    });

    _eventHandler->addGod(WICHGOD::WATER, [](const std::string& action) {
        std::cout << "God Water Received Message: " << action << std::endl;
    });

    _eventHandler->addGod(WICHGOD::EARTH, [](const std::string& action) {
        std::cout << "God EARTH Received Message: " << action << std::endl;
    });

    _eventHandler->addGod(WICHGOD::WIND, [](const std::string& action) {
        std::cout << "God WIND Received Message: " << action << std::endl;
    });

    std::thread([_eventHandler] { _eventHandler->sendMessage(WATER, "Hello from AIR");   m_done.fetch_add(1, std::memory_order_relaxed) ;}).detach();
    std::thread([_eventHandler] { _eventHandler->sendMessage(AIR, "Hello from WATER");   m_done.fetch_add(1, std::memory_order_relaxed); }).detach();
    std::thread([_eventHandler] { _eventHandler->sendMessage(EARTH, "Hello from WATER"); m_done.fetch_add(1, std::memory_order_relaxed); }).detach();
    std::thread([_eventHandler] { _eventHandler->sendMessage(WIND, "Hello from WATER");  m_done.fetch_add(1, std::memory_order_relaxed); }).detach();

    while (m_done.load() < 4) {
        std::this_thread::yield();
    }
    return 0;
}
