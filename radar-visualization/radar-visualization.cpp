// radar-visualization.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Game.h"

int main()
{
    // Init rand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init Game Engine
    Game game;

    // Game loop
    while (game.running())
    {
        // Update
        game.update();

        // Render
        game.render();
    }
    // End of application
    return 0;
}

