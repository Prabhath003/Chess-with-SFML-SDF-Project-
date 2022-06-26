#pragma once

// including the librarues
#include <vector>

// including the files
#include "MainMenu.hpp"
#include "StartMenu.hpp"
#include "FreePlay.hpp"
#include "RapidPlay.hpp"
#include "FritzPlay.hpp"
#include "BulletPlay.hpp"
#include "CustomPlay.hpp"
#include "LearnChess.hpp"
#include "LearnChessb.hpp"
#include "About.hpp"

namespace Engine
{
    // class to handle and execute the states
    class Game
    {
        private:
            std::shared_ptr<sf::RenderWindow> window; // creating a sfml window 
            std::shared_ptr<State> x_state; // creating a temporary variable for states
            std::vector<std::shared_ptr<State>> n_states; // creating a vector to store the states
            
            void makeStates(); // function to push the states into the vector

        public:
            
            Game();

            void run(); // function to run the states
    };
}