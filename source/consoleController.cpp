/**
 * @file consoleController.cpp
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Console controller class file
 * @version 0.1
 * @date 14-12-2022
 *
 * @copyright Copyright (c) 2022
 */

#include "consoleController.h"

consoleController::consoleController(/* args */)
{
}

consoleController::~consoleController()
{
}

bool consoleController::run()
{
    try
    {
        mThread = std::thread(&consoleController::threadFunc, this);
    }
    catch (...)
    {
        return false;
    }
    return true;
}

void consoleController::threadFunc()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        try
        {
            m.lock();
            if (!q.empty())
            {
                std::cout << q.front() << std::endl;
                q.pop();
            }
            m.unlock();
        }
        catch (std::runtime_error &e)
        {
            std::cout << "Console Controller Runtime Error" << std::endl;
            throw;
        }
        catch (...)
        {
            std::cout << "Console Controller Unknown Error" << std::endl;
            throw;
        }
    }
}

void consoleController::consoleWrite(std::string message)
{
    m.lock();
    q.push(message);
    m.unlock();
}