/**
 * @file autoSprayer.h
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Automatic sprayer class header file
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
#include "consoleController.h"

#ifndef AUTO_SPRAYER_H
#define AUTO_SPRAYER_H

/**
 * @brief This class controls the sprayer attachment
 */
class autoSprayer
{
private:
    std::thread mThread;
    consoleController *mConsole;
    /**
     * @brief Sprayer I/O thread
     */
    void threadFunc();
public:
    /**
     * @brief Create the auto sprayer object
     */
    autoSprayer(/* args */);
    /**
     * @brief Destroy the auto sprayer object
     */
    ~autoSprayer();
    /**
     * @brief Run the console control task
     *
     * @return true Init OK
     * @return false Init error
     */
    bool run();
    /**
     * @brief Set the console controller object
     * 
     * @param console Console object
     */
    void setConsoleController(consoleController *console);
};

#endif