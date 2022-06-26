#pragma once

// including the Game type file
#include "GameType.hpp"

// deriving the rapid play from GameType class
class RapidPlay 
#define BASES public GameType
    : BASES
{
    private:
        void Variables();                   // function to define the variables

    public:
typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#undef BASES
        RapidPlay(std::shared_ptr<sf::RenderWindow> &x_window); // taking sfml window

        // overriding function from the State class to check the input from the user
        void Input(sf::Event &event, std::shared_ptr<State> &xState,
            std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Input);
        // overriding function from the State class to implement logic based on input
        void Logic(boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Logic);
        // overriding function from the State class to draw the items
        void Draw(boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Draw);
};