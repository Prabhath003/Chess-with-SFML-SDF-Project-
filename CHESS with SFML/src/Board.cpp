#include "Board.hpp"

Board::Board(std::shared_ptr<sf::RenderWindow> &x_window, sf::Color col1, sf::Color col2)
    : window(x_window)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(size == window->getSize().y / 12);
        })
    ;
    size = (2 * window->getSize().y / 3) / 8;
    
    load(col1,col2);
}

// Member function that sets Board stuff, can choose square colors in parameters
void Board::load(sf::Color col1, sf::Color col2)
{
    for(int i=0; i<8;i++)
    {
        bool tmpColor = ((i % 2) == 0) ? true : false;
        for(int j = 0; j < 8; j++)
        {
            m_boardSquares[j + (i * 8)].setPosition(sf::Vector2f((j - 4 ) * size + window->getSize().x / 2,
                (i -4) * size + window->getSize().y / 2));
            m_boardSquares[j + (i * 8)].setSize(sf::Vector2f(size, size));
            m_boardSquares[j + (i * 8)].setFillColor(tmpColor ? col1 : col2);
            
            tmpColor = !tmpColor;
        }
    }
}

// Draw class on SFML Window
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.combine(getTransform());
    for(int i = 0; i < 64;i++)
    {
        target.draw(m_boardSquares[i]);
    }
}