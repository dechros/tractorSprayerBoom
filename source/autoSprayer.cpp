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
    mSensorDetectedField = false;
    mAutoSprayerEngaged = false;
    attachmentPosition = ATTACHMENT_POSITION_MAX;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        try
        {
            /* Get the button and sensor variables updated */
            updateVariables();
            if ((mAutoSprayerEngaged == false) || (mSensorDetectedField == false))
            {
                mConsole->consoleWrite("Ergo button is disabled.");
                /* Prepare the attachment for turning */
                lockTheWheels(false);
                mConsole->consoleWrite("Wheels are unlocked.");
                if (attachmentPosition < ATTACHMENT_POSITION_MAX)
                {
                    mConsole->consoleWrite("Attachment is going to top. Position : " + std::to_string(attachmentPosition));
                    driveAttachment(ATTACHMENT_POSITION_UP);
                }
                else
                {
                    mConsole->consoleWrite("Attachment is locked at top.");
                }
            }
            else
            {
                mConsole->consoleWrite("Ergo button is enabled.");
                /* Prepare the attachment for spraying */
                lockTheWheels(true);
                mConsole->consoleWrite("Wheels are locked.");
                if (attachmentPosition > ATTACHMENT_POSITION_MIN)
                {
                    mConsole->consoleWrite("Attachment is going to bottom. Position : " + std::to_string(attachmentPosition));
                    driveAttachment(ATTACHMENT_POSITION_DOWN);
                }
                else
                {
                    mConsole->consoleWrite("Attachment is locked at bottom.");
                }
            }
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

void autoSprayer::setSimulationController(simulationController *simulation)
{
    mSimulation = simulation;
}

void autoSprayer::updateVariables()
{
    mSensorDetectedField = mSimulation->getSensorData();
    mAutoSprayerEngaged = mSimulation->getButtonEnableData();
}

void autoSprayer::driveAttachment(int movementPosition)
{
    if (movementPosition == ATTACHMENT_POSITION_UP)
    {
        attachmentPosition++;
    }
    else if (movementPosition == ATTACHMENT_POSITION_DOWN)
    {
        attachmentPosition--;
    }
}

bool autoSprayer::lockTheWheels(bool status)
{
    /* We should check wheel position here */
    return status;
}