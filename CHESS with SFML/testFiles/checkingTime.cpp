#include <gtest/gtest.h>

#include "RapidPlay.hpp"
#include "FritzPlay.hpp"
#include "CustomPlay.hpp"
#include "BulletPlay.hpp"

TEST(rapidPlay, checktimelimit)
{
    std::shared_ptr<sf::RenderWindow> window;
    window = std::make_shared<sf::RenderWindow>();

    RapidPlay play(window);
    ASSERT_EQ(play.getTimeLimit(), 35*60);
}

TEST(fritzPlay, checktimelimit)
{
    std::shared_ptr<sf::RenderWindow> window;
    window = std::make_shared<sf::RenderWindow>();

    FritzPlay play(window);
    ASSERT_EQ(play.getTimeLimit(), 7*60);
}

TEST(customPlay, checktimelimit)
{
    std::shared_ptr<sf::RenderWindow> window;
    window = std::make_shared<sf::RenderWindow>();

    CustomPlay play(window);
    ASSERT_GE(play.getTimeLimit(), 10);
}

TEST(bulletPLay, checktimelimit)
{
    std::shared_ptr<sf::RenderWindow> window;
    window = std::make_shared<sf::RenderWindow>();

    BulletPlay play(window);
    ASSERT_GE(play.getTimeLimit(), 90);
}