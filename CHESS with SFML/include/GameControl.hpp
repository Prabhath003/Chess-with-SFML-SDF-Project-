#pragma once

// including the files
#include "Algo.hpp"
#include "State.hpp"

// class to handle the algo
class GameControl
{
    private:
        std::shared_ptr<sf::RenderWindow> window; // render window
        ChessGame *chess; // pointer to chess algo
        float size, halfWx, halfWy; // variables declared to use repeatedly
        bool restartSelected; // boolean to check the restart button

    public:
        GameControl(std::shared_ptr<sf::RenderWindow> &x_window); // taking the render window

        void runAlgo(sf::Event &event); // function to Run Algo
        bool reset(sf::Event &event);   // function to reset the things
        void draw(); // function to draw the things
        ChessGame* getchess(); // function to get the chess pointer
};