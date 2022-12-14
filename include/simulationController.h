/**
 * @file simulationController.h
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Simulation controller class header file
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

#ifndef SIMULATION_CONTROLLER_H
#define SIMULATION_CONTROLLER_H

#define MAX_FIELD_LENGTH 10
#define MIN_FIELD_LENGTH 0

#define MAX_TRACTOR_RANGE 15
#define MIN_TRACTOR_RANGE -5

#define MAX_SPRAY_LINES 5
#define MIN_SPRAY_LINES 0

#define TRACTOR_POSITION_UP 0
#define TRACTOR_POSITION_DOWN 1

/**
 * @brief This class controls the simulation
 */
class simulationController
{
private:
    bool mAutoSprayerEnabled;
    bool mAutoSprayerEngaged;
    int mCurrentLength;
    int mCurrentSprayLine;
    int mTractorPosition;
    std::thread mThread;
    consoleController *mConsole;
    mutable std::mutex m;
    /**
     * @brief Simulation control thread
     */
    void threadFunc();
public:
    /**
     * @brief Create the simulation controller object
     */
    simulationController(/* args */);
    /**
     * @brief Destroy the simulation controller object
     */
    ~simulationController();
    /**
     * @brief Run the simulation control task
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
    /**
     * @brief Indicates sensor data for the field
     * 
     * @return true Sensor sees the field
     * @return false Sensor can not see the field
     */
    bool getSensorData();
    /**
     * @brief Indicates button data for the field
     * 
     * @return true Auto spray is enabled
     * @return false Auto spray is disabled
     */
    bool getButtonEnableData();
};

#endif