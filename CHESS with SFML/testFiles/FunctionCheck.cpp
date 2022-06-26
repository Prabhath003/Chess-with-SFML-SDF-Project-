#include <gtest/gtest.h>

#include "Algo.hpp"

TEST(FunctionCheck, If_Points_added_when_blackPiece_dead)
{
    std::shared_ptr<sf::RenderWindow> window;
    window = std::make_shared<sf::RenderWindow>();
    sf::Color c1 = sf::Color::White;
    sf::Color c2 = sf::Color::Black;
    ChessGame c(window,c1,c2);

    std::vector<Piece*>& bp = c.getBlackPieces();
    bp.at(6)->setPosition(-1);
    c.PointsCalculator();

    EXPECT_EQ(c.getWhiteScore(),3); // Checking function
    EXPECT_EQ(c.pointsCheck(6,false),true); // Checking function
}