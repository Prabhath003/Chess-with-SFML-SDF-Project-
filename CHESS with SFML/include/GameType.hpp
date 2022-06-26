#pragma once

// including the files
#include "State.hpp"
#include "GameControl.hpp"

// class declaring in general to create differnt game play states
class GameType
#define BASES public Engine::State
    : BASES
{
    protected:
        sf::RectangleShape backscreen;      //
        sf::Text purpose;                   // variables used on the game Over screen
        sf::Text winner;                    //
        sf::Text replay;                    //
        sf::RectangleShape uparrow;         // shape to draw the arrow marks to set the time
        sf::RectangleShape downarrow;       //
        sf::Text setTime;                   // text variable to show the set time
        int sethr, setmin, setsec, setTotalTime;   // time limits

        sf::Text back;                      //
        sf::Text name;                      // variables used on the main screen
        sf::Text showMoves;                 // text variable to on/off highlight moves
        sf::CircleShape On;                 // shape to show the status of highlightmoves
        GameControl *game;                  // creating pointer of gameCOntrol class

        bool backButton;                    //
        bool operate;                       // boolean variables to check the input
        bool replayButton;                  //
        bool timeLimit;                     //
        bool firstTime;                     //
        bool highLightMoves;                //
        bool showMovesButton;               //

        void Variables();                   // function to define the variables

    public:
typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#undef BASES
        GameType(std::shared_ptr<sf::RenderWindow> &x_window); // taking sfml window

        // overriding function from the State class to check the input from the user
        void Input(sf::Event &event, std::shared_ptr<State> &xState,
            std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Input); // boost checking the overriding
        // overriding function from the State class to implement logic based on input
        void Logic(boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Logic);
        // overriding function from the State class to draw the items
        void Draw(boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(Draw);

        int getTimeLimit();
};