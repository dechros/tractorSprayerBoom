/**
 * @file main.cpp
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Tractor attachment boom sprayer program
 * @version 0.1
 * @date 04-12-2022
 *
 * @copyright Copyright (c) 2022
 */

#include <iostream>
#include "autoSprayer.h"
#include "consoleController.h"
#include "simulationController.h"

/**
 * @brief Enterance point of the program
 *
 * @return int Program succes value
 */
int main(void)
{
    /* Object Creation */
    consoleController console;
    simulationController simulation;
    autoSprayer sprayer;
    
    /* Setting the relationships */
    sprayer.setConsoleController(&console);
    sprayer.setSimulationController(&simulation);
    simulation.setConsoleController(&console);
    
    /* Creating the threads*/
    if (console.run() == false)
    {
        std::cout << "Console Thread Init Error" << std::endl;
    }
    else
    {
        console.consoleWrite("Console Thread OK");
    }
    if (simulation.run() == false)
    {
        console.consoleWrite("Simulation Thread Init Error");
    }
    else
    {
        console.consoleWrite("Simulation Thread OK");
    }
    if (sprayer.run() == false)
    {
        console.consoleWrite("Sprayer Thread Init Error");
    }
    else
    {
        console.consoleWrite("Sprayer Thread OK");
    }
    
    /* Main function should remain inactive */
    while (1)
    {
        std::this_thread::yield();
    }
    return 0;
}