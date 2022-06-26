#include "GameControl.hpp"

GameControl::GameControl(std::shared_ptr<sf::RenderWindow> &x_window) : window(x_window)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(chess != nullptr);
            BOOST_CONTRACT_ASSERT(size == window->getSize().y / 12);
            BOOST_CONTRACT_ASSERT(halfWx == window->getSize().x / 2);
            BOOST_CONTRACT_ASSERT(halfWy == window->getSize().y / 2);;
        })
    ;

    chess = new ChessGame(window, sf::Color(0xf3bc7aff),sf::Color(0xae722bff));
    size = (2 * window->getSize().y / 3) / 8;
    halfWx = window->getSize().x / 2;
    halfWy = window->getSize().y / 2;
}

void GameControl::runAlgo(sf::Event &event)
{
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if((halfWx - 4 * size <= event.mouseButton.x) && (event.mouseButton.x <= halfWx + 4 * size) &&
                (halfWy - 4 * size <= event.mouseButton.y) && (event.mouseButton.y <= halfWy + 4 * size))
            {
                unsigned int buttonPos{unsigned((event.mouseButton.x - halfWx + 4 * size) / size) +
                    unsigned(((event.mouseButton.y - halfWy + 4 * size) / size)) * 8};
                                                    
                if(!chess->getSelected())
                    chess->selectPiece(buttonPos);
                else
                    chess->moveSelected(buttonPos);
            }
        }
    }
}

bool GameControl::reset(sf::Event &event)
{
    if(event.type == sf::Event::MouseMoved)
        restartSelected = chess->getRestart().getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y) ? true : false;
    if(restartSelected && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
       chess->restart();
        return true;
    }
    return false;
}

ChessGame* GameControl::getchess()
{
    return chess;
}

void GameControl::draw()
{
    window->draw(*chess);
}