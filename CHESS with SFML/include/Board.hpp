#pragma once

// inlcluding the libraries
#include <SFML/Graphics.hpp>
#include <memory>
#include <array>
#include <boost/contract.hpp>

// Board class to draw the Board
class Board : public sf::Drawable, public sf::Transformable
{
    private:
        std::shared_ptr<sf::RenderWindow> window; // sfl render window
        float size; // variable to store the side lenght of each block

        std::array<sf::RectangleShape, 64> m_boardSquares; // creating array of 64 squares
        
        // Draw class on SFML Window
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        // contructor taking the render window and two colors
        Board(std::shared_ptr<sf::RenderWindow> &x_window, sf::Color col1 = sf::Color::White, sf::Color col2 = sf::Color::Black);
        // Member function that sets Board stuff, can choose square colors in parameters
        void load(sf::Color col1 = sf::Color::White, sf::Color col2 = sf::Color::Black);
};