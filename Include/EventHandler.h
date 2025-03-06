#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <functional> //using for function pointer
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <variant> // For accept both 2 different callback
#include <mutex>
#include <thread>

enum WICHGOD {
    WATER,
    AIR,
    EARTH,
    WIND
};

class EventHandler {

public:
    template<typename functionPointer>
    using Callback = std::function<functionPointer>;

    /**
    * @brief Adds a God and Set Actions for theme
    *
    * @param god The God to be added.
    * @param action The action associated with the God.
    */
    template<typename typeInput>
    //Implementation universal callback
    void addGod(WICHGOD god, typeInput&& callback)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_connections[god] = std::forward<typeInput>(callback);
        m_listEvents.push_back(callback);
    }

    /**
    * @brief Send Message to gods
    *
    * @param god find that god function pointer.
    * @param value for set that string god action.
    */

    void sendMessage(WICHGOD god, std::string value)
    {
        //I use lock_guard because unique_guard has overhead
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_connections.find(god);

        //Check call back exists or not
        if (it == m_connections.end()) {
            std::cerr << "No _callback found for " << god << std::endl;
            return;
        }

        auto _callback = it->second; // Copy _callback before unlocking mutex

         std::visit(
                 [value](auto&& func) {
                        using T = std::decay_t<decltype(func)>;
                        if constexpr (std::is_same_v<T, Callback<void()>>) {
                            func();
                        } else if constexpr (std::is_same_v<T, Callback<void(const std::string&)>>) {
                            func(value);

                        }
                    }, _callback
            );
    }


private:
    std::unordered_map<WICHGOD, std::variant<
            Callback<void()>,
            Callback<void(const std::string&)>
    >> m_connections;

    std::vector<std::variant<
            Callback<void()>,
            Callback<void(const std::string&)>
    >> m_listEvents;

    mutable std::mutex m_mutex;
};

#endif //EVENTHANDLER_H
