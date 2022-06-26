#include <gtest/gtest.h>

#include "Algo.hpp"

TEST(TurnTest, CheckIfWhiteFirst)
{
    std::shared_ptr<sf::RenderWindow> window;
    window = std::make_shared<sf::RenderWindow>();
    sf::Color c1 = sf::Color::White;
    sf::Color c2 = sf::Color::Black;
    ChessGame c(window,c1,c2);

    ASSERT_EQ(c.getPlayerTurn(),true);
}