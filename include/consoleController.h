/**
 * @file consoleController.h
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Console controller class header file
 * @version 0.1
 * @date 14-12-2022
 *
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <functional>
#include <stdexcept>
#include <chrono>
#include <queue>
#include <mutex>

#ifndef CONSOLE_CONTROLLER_H
#define CONSOLE_CONTROLLER_H

/**
 * @brief This class controls console I/O
 */
class consoleController
{
private:
    std::thread mThread;
    std::queue<std::string> q;
    mutable std::mutex m;
    /**
     * @brief Console I/O thread
     */
    void threadFunc();
public:
    /**
     * @brief Create the console controller object
     */
    consoleController(/* args */);
    /**
     * @brief Destroy the console controller object
     */
    ~consoleController();
    /**
     * @brief Run the console control task
     *
     * @return true Init OK
     * @return false Init error
     */
    bool run();
    /**
     * @brief Thread safe console write function
     *
     * @param message Console message to be written
     */
    void consoleWrite(std::string message);
};

#endif