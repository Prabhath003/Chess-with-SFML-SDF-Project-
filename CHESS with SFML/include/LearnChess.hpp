#pragma once

// including files
#include "State.hpp"

// LearnChess state to show how to play chess
class LearnChess
#define BASES public Engine::State
    : BASES
{
    private:
        sf::Text name;  // text to show the title

        sf::Text intro;         //
        sf::Text King;          //
        sf::Text KingC;         //
        sf::Text Queen;         //
        sf::Text QueenC;        //
        sf::Text Bishop;        // text variables to write the matter
        sf::Text BishopC;       //
        sf::Text Rook;          //
        sf::Text RookC;         //
        sf::Text Knight;        //
        sf::Text KnightC;       //
        sf::Text Pawn;          //
        sf::Text PawnC;         //

        sf::Text back;      //
        sf::Text next;      // variables to navigate

        bool backButton;    //
        bool nextButton;    // to check the navigations

        void Variables();                   // function to define the variables

    public:
typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#undef BASES
        LearnChess(std::shared_ptr<sf::RenderWindow> &x_window); // taking sfml window

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