#pragma once

// Libraries used
#include <vector>
#include <utility>

// including the required files
#include "Board.hpp"
#include "Piece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Pawn.hpp"

// class derived from the sfml classes to draw the coins on the board after every move
class ChessGame: public sf::Drawable, public sf::Transformable
{
    private:
        std::shared_ptr<sf::RenderWindow> window; // sfml render window
        float size; // variable to set the side lenght of each square of Board;
        Board board; // creating Board class to draw the Board
        std::vector<Piece*> whitePieces;    // 
        std::vector<Piece*> blackPieces;    // vectors to create the coins 
        Piece* selectedPiece; // pointer the points to the selected piece
        std::vector<sf::RectangleShape> possibleMovesSquares; // vector to store the possible moves square
        std::string lastMove; // string to store the info of last move

        sf::RectangleShape infoRestart; // the rectangle shape to draw around the restart text

        sf::Font font;              // font variable to store the a font texture
        sf::Text score;             //
        sf::Text textRestart;       //
        sf::Text textTurn;          // text variable used in this window
        sf::Text textSituation;     //
        sf::Text textLastMove;      //

        bool selected;    // boolean to check a piece is selected
        bool playerTurn; // true = White turn, false = Black Turn
        bool playerTurnCheck; // boolean to check if its player turn
        bool mate; // to check the mate
        int turn; // integer to check the turn
        int winner; // 1->white, 0->draw, -1->black, 2->not decided
        bool highlightMoves; // all possible moves for a piece will highlighted if true

        int WhiteScore = 0,BlackScore = 0; // integers to store the score
        std::vector<std::pair<int,bool>> pieceDeadIndex; // true = white; false = black;

        void createMovesSquares();      // function to create the possibleMoveSquares vector
        void calcPossibleMoves();       // function to calc the Possible Moves
        void calcCastling(Piece* tmpPiece); // calcCastling
        void eraseMoves(Piece* tmpPiece);  // funciton to erase the invalid moves
        void checkMate(); // function to verify checkmate
        void updateInfo();  // functino to update info

        void SetScore(); // function to set the updated score

        // function from the sfml class being overrided
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        // contructor taking the render window and two colors
        ChessGame(std::shared_ptr<sf::RenderWindow> &x_window, sf::Color bordCol1, sf::Color bordCol2);

        bool getSelected(){return selected;}    //
        bool getMate(){return mate;}            // function to get the boolean value of variable
        bool selectPiece(int pos);              // function to select the piece
        void moveSelected(int pos);             // function to move the piece
        void restart();                         // function to restart
        bool getPlayerTurn();                   // function which returns whose turn
        bool pointsCheck(int i,bool r);         // function to check does it been counted for points
        sf::RectangleShape getRestart();        // function to get the restart variable
        int getWinner();                        // function to get the integral value of winner
        int getBlackScore();                    // function to get Black score
        int getWhiteScore();                    // function to get White score
        void toggleHighlightMoves(bool value);  // function to change boolean value of highlidgtMoves
        void PromotePawn();                     // function to check and promote the Pawn to Queen
        void PointsCalculator(); // fuction to update the score
        std::vector<Piece*>& getWhitePieces();
        std::vector<Piece*>& getBlackPieces();
};