/**
 * @file autoSprayer.cpp
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Automatic sprayer class file
 * @version 0.1
 * @date 14-12-2022
 *
 * @copyright Copyright (c) 2022
 */

#include "autoSprayer.h"

autoSprayer::autoSprayer(/* args */)
{
}

autoSprayer::~autoSprayer()
{
}

bool autoSprayer::run()
{
    try
    {
        mThread = std::thread(&autoSprayer::threadFunc, this);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

void autoSprayer::threadFunc()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        try
        {
            mConsole->consoleWrite("Auto Sprayer Running");
        }
        catch (std::runtime_error &e)
        {
            std::cout << "Auto Sprayer Runtime Error" << std::endl;
            throw;
        }
        catch (...)
        {
            std::cout << "Auto Sprayer Unknown Error" << std::endl;
            throw;
        }
    }
}

void autoSprayer::setConsoleController(consoleController *console)
{
    mConsole = console;
}