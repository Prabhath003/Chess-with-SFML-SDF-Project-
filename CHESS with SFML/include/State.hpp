// Code will only be loaded once
#pragma once

// Memory header
#include <memory>
// header to control timers
#include <chrono>

// Header including the data file
#include "Data.hpp"

namespace Engine
{
    // Enum to call states pushed into vector in Game.hpp
    enum states
    {
        Main_Menu,
        Start_Menu,
        Free_Play,
        Rapid_Play,
        Fritz_Play,
        Bullet_Play,
        Custom_Play,
        Learn_Chess,
        Learn_Chessb,
        about
    };
    
    // Creating a class State which controls different sfml functions
    class State
    {
        protected:
            // Making a shared_ptr of SFML Render Window to be used everywhere 
            std::shared_ptr<sf::RenderWindow> window;
            // Creating the data class containing the data about the textures 
            Data data;
            // Creating a SFML Rectangle Shape to use as back ground 
            sf::RectangleShape backGround;

            // variables to handle time
            int hr, min, sec;
            std::chrono::duration<double> timecountsec;
            sf::Text time;
            std::string tempTime;
            std::chrono::steady_clock::time_point end;
            
            // Function to initiallise variables in this class
            void Variables();

            // Function used to set the parameters to a SFML Text variable
            void Set_Text(sf::Text &name, sf::Font &tex, std::string s, size_t character_size, float pos_x,
                float pos_y);
            // Function to give a boolean value to the button variable using other parameters
            void Menu_input(sf::Text &name, bool &button, sf::Event &event);
            // Function to Highlight the SFML Texture by changing color
            void Highlight_options(bool &button, sf::Text &name);

            // Function to calculate time passed in a state    
            void calculateTime();

        public:
            // Class Contructor taking the SFML Render Window Variable and putting that in the default variable
            State(std::shared_ptr<sf::RenderWindow> &x_window);
            
            // creating the start point variable to fix a start point for timer
            std::chrono::steady_clock::time_point start;

            // Function to take input from the user using SFML
            virtual void Input(sf::Event &event, std::shared_ptr<State> &xState,
                std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v = 0) = 0;
            // Function to check the input given by the user using SFML
            virtual void Logic(boost::contract::virtual_ *v = 0) = 0;
            // Function to draw objects using SFML
            virtual void Draw(boost::contract::virtual_ *v = 0) = 0;
    };
} // namespace Engine