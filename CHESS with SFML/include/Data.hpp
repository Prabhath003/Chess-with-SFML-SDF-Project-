#pragma once

// including the libraries
#include <SFML/Graphics.hpp>
#include <boost/contract.hpp> // boost library to write the contracts
#include <memory>
#include <iostream>

namespace Engine
{    
    class Data
    {
        public:
            //Textures:
            // for backgrounds
            sf::Texture tex_BackGround;

            // for fonts
            sf::Font Beams_font;
            sf::Font Pacifico_font;
            sf::Font Round_Bold;

            // for Chess Board Blocks
            sf::Texture tex_BBox;
            sf::Texture tex_WBox;
            sf::Texture tex_arrow;

            // for Black coins
            static sf::Texture blackKing;
            static sf::Texture blackQueen;
            static sf::Texture blackRook;
            static sf::Texture blackKnight;
            static sf::Texture blackBishop;
            static sf::Texture blackPawn;

            // for White coins
            static sf::Texture whiteKing;
            static sf::Texture whiteQueen;
            static sf::Texture whiteRook;
            static sf::Texture whiteKnight;
            static sf::Texture whiteBishop;
            static sf::Texture whitePawn;

            static sf::Texture loadTexture(std::string str); // function to load the textures

            Data();
    };    
} // namespace Engine