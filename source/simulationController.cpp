/**
 * @file simulationController.cpp
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Simulation controller class file
 * @version 0.1
 * @date 14-12-2022
 *
 * @copyright Copyright (c) 2022
 */

#include "simulationController.h"

simulationController::simulationController(/* args */)
{
    mSensorDetectedField = false;
    mAutoSprayerEngaged = true;
    mCurrentLength = MIN_TRACTOR_RANGE;
    mCurrentSprayLine = MIN_SPRAY_LINES;
    mTractorPosition = TRACTOR_POSITION_UP;
}

simulationController::~simulationController()
{
}

bool simulationController::run()
{
    try
    {
        mThread = std::thread(&simulationController::threadFunc, this);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

void simulationController::threadFunc()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        try
        {
            /* Update the Tractor Location Info*/
            if (mTractorPosition == TRACTOR_POSITION_UP)
            {
                mConsole->consoleWrite("                                            Tractor position Up");
                mCurrentLength++;
                if (mCurrentLength >= MAX_TRACTOR_RANGE)
                {
                    mTractorPosition = TRACTOR_POSITION_DOWN;
                    mCurrentSprayLine++;
                }
            }
            else if (mTractorPosition == TRACTOR_POSITION_DOWN)
            {
                mConsole->consoleWrite("                                            Tractor position Down");
                mCurrentLength--;
                if (mCurrentLength <= MIN_TRACTOR_RANGE)
                {
                    mTractorPosition = TRACTOR_POSITION_UP;
                    mCurrentSprayLine++;
                }
            }
            else
            {
                mConsole->consoleWrite("                                            Simulation Controller Tractor Position Error");
            }

            /* Maximum spray lines determines if the simulation is done or not */
            if (mCurrentSprayLine >= MAX_SPRAY_LINES)
            {
                mConsole->consoleWrite("                                            Simulation is done.");
                return;
            }

            /* The location of the tractor in the field determines the sensor data */
            if (mCurrentLength < MIN_FIELD_LENGTH || mCurrentLength > MAX_FIELD_LENGTH)
            {
                mConsole->consoleWrite("                                            Tractor is out of the field.");
                m.lock();
                mSensorDetectedField = false;
                m.unlock();
            }
            else
            {
                mConsole->consoleWrite("                                            Tractor is in the field.");
                m.lock();
                mSensorDetectedField = true;
                m.unlock();
            }
        }
        catch (std::runtime_error &e)
        {
            std::cout << "Simulation Controller Runtime Error" << std::endl;
            throw;
        }
        catch (...)
        {
            std::cout << "Simulation Controller Unknown Error" << std::endl;
            throw;
        }
    }
}

void simulationController::setConsoleController(consoleController *console)
{
    mConsole = console;
}

bool simulationController::getSensorData()
{
    bool retVal = false;
    m.lock();
    retVal = mSensorDetectedField;
    m.unlock();
    return retVal;
}

bool simulationController::getButtonEnableData()
{
    bool retVal = false;
    m.lock();
    retVal = mAutoSprayerEngaged;
    m.unlock();
    return retVal;
}