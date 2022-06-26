#pragma once

// including the State library
#include "State.hpp"

// State About to show the time periods of different Plays derived from the State class
class About
#define BASES public Engine::State
    : BASES
{
    private:
        sf::Text name;    //
        sf::Text Types;   // text variable used in this state
        sf::Text back;    //

        bool backButton;  // boolean to check the input from user

        void Variables();                   // function to define the variables

    public:
typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#undef BASES
        About(std::shared_ptr<sf::RenderWindow> &x_window); // taking sfml window

        // overriding function from the State class to check the input from the user
        void Input(sf::Event &event, std::shared_ptr<State> &xState,
            std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Input);  // Boost contracts to check the overriding
        // overriding function from the State class to implement logic based on input
        void Logic(boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Logic);
        // overriding function from the State class to draw the items
        void Draw(boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Draw);
};