#pragma once

// including the files
#include "State.hpp"

// Mainmenu class
class MainMenu
#define BASES public Engine::State
        : BASES
    {
        private:
            sf::Text title;         //
            sf::Text start;         // variables used in this state
            sf::Text learnChess;    //
            sf::Text about;         //
            sf::Text exit;          //

            bool startButton;       //
            bool learnChessButton;  // variables to check the user input
            bool aboutButton;       //
            bool exitButton;        //

            void Variables();       // function to define the variables

        public:
typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#undef BASES
            MainMenu(std::shared_ptr<sf::RenderWindow> &x_window); // taking the render window

            // overriding function from the State class to check the input from the user
            void Input(sf::Event &event, std::shared_ptr<State> &xState,
                std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v = 0) override;
            BOOST_CONTRACT_OVERRIDE(Input); // boost checking the overridings
            // overriding function from the State class to implement logic based on input
            void Logic(boost::contract::virtual_ *v = 0) override;
            BOOST_CONTRACT_OVERRIDE(Logic);
            // overriding function from the State class to draw the items
            void Draw(boost::contract::virtual_ *v = 0) override;
            BOOST_CONTRACT_OVERRIDE(Draw);
    };
