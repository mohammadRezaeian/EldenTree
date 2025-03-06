#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>
#include "EventHandler.h"

class EventHandlerTest : public testing::Test {
protected:
    std::mutex mtx; // Mutex to protect the flags
    bool airReceived = false;
    bool waterReceived = false;
    bool earthReceived = false;
    bool windReceived = false;

    // Helper function to set the flags safely inside the mutex
    void setFlag(bool& flag, bool value) {
        std::lock_guard<std::mutex> lock(mtx);
        flag = value;
    }
};

// Test case for adding gods and sending messages
TEST_F(EventHandlerTest, TestMessageDispatch) {

    auto eventHandler = std::make_shared<EventHandler>();

    // Add gods with simple action handlers
    eventHandler->addGod(WICHGOD::AIR, [this](const std::string& action) {
        if (action == "Hello from WATER") {
            setFlag(airReceived, true);
        }
    });

    eventHandler->addGod(WICHGOD::WATER, [this](const std::string& action) {
        if (action == "Hello from AIR") {
            setFlag(waterReceived, true);
        }
    });

    eventHandler->addGod(WICHGOD::EARTH, [this](const std::string& action) {
        if (action == "Hello from WATER") {
            setFlag(earthReceived, true);
        }
    });

    eventHandler->addGod(WICHGOD::WIND, [this](const std::string& action) {
        if (action == "Hello from WATER") {
            setFlag(windReceived, true);
        }
    });

    std::thread([eventHandler] {
        eventHandler->sendMessage(WICHGOD::WATER, "Hello from AIR");
    }).detach();

    std::thread([eventHandler] {
        eventHandler->sendMessage(WICHGOD::AIR, "Hello from WATER");
    }).detach();

    std::thread([eventHandler] {
        eventHandler->sendMessage(WICHGOD::EARTH, "Hello from WATER");
    }).detach();

    std::thread([eventHandler] {
        eventHandler->sendMessage(WICHGOD::WIND, "Hello from WATER");
    }).detach();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    {
        std::lock_guard<std::mutex> lock(mtx);
        EXPECT_TRUE(airReceived);
        EXPECT_TRUE(waterReceived);
        EXPECT_TRUE(earthReceived);
        EXPECT_TRUE(windReceived);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
