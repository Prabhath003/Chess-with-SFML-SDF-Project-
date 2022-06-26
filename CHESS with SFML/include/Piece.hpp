#pragma once

// including the libraries
#include <string>
#include <vector>
#include <array>

// including the files
#include "Data.hpp"

// general base piece class derived from sfml drawable classes 
class Piece : public sf::Drawable, public sf::Transformable
{
    private:
        std::shared_ptr<sf::RenderWindow> window; // render window

    protected:
        float size; // float to store the side lenght of each square block
        sf::RectangleShape m_sprite;    // variable to store the texture of piece
        std::vector<int> possibleMoves; // vector to store the possible moves
        std::vector<int> dangerMoves; // Moves that endanger opposite king

        char m_type; //'K'=King , 'Q' = Queen , 'R' = Rook , 'B' = Bishop , 'N' = Knight , 'P' = Pawn
        bool m_player; // true == White , false == Black
        int m_position; // 0-63 board, -1 dead
        int enPassant; // variable to check enPassant
        bool m_moved; // variable to check whether moves

        void setTexture(); // function to set the texture
        void move();       // function to move

        // function to draw the piece
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        // constructor
        Piece(char type = 'P', bool player = true, int pos = -1, bool moved = false);

        void setWindow(std::shared_ptr<sf::RenderWindow> &x_window); // taking the window
        char getType(); // function to get the type
        bool getPlayer(); // function to get the value of player
        void setPosition(int pos); // function to set position
        int getPosition(); // function to get the position
        void setMoved(bool moved); // function to set the status of move
        bool getMoved(); // function to get the status of move
        void setEnPassant(int x); // function to se the enPassant
        int getEnPassant(); // function to get the enPassant

        // function to calculate the possible moves
        virtual void calcMoves(std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces,
            bool playerTurn, boost::contract::virtual_ *v = 0) = 0;

        std::vector<int>& getPossibleMoves(); // function to get the possible moves
        std::vector<int>& getDangerMoves(); // function to get the danger moves
        std::string toString(); // function to return the the string showing of the move
};