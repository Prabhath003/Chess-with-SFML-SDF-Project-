#pragma once

// including files
#include "State.hpp"

// LearnChess state to show how to play chess
class LearnChessb
#define BASES public Engine::State
    : BASES
{
    private:
        sf::Text name;      // text to show the title

        sf::Text note;      // 
        sf::Text special;   //
        sf::Text castling;  //
        sf::Text castlingC; //
        sf::Text enPassant; //
        sf::Text enPassantC;// text variables to write the matter
        sf::Text check;     //
        sf::Text checkC;    //
        sf::Text mate;      //
        sf::Text mateC;     //
        sf::Text draw;      //
        sf::Text drawC;     //

        sf::Text back; // variables to navigate

        bool backButton; // to check the navigations

        void Variables();                   // function to define the variables

    public:
typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#undef BASES
        LearnChessb(std::shared_ptr<sf::RenderWindow> &x_window); // taking sfml window

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