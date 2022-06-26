#include "Game.hpp"

Engine::Game::Game()
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(x_state == n_states.at(states::Main_Menu));
        })
    ;

    window = std::make_shared<sf::RenderWindow>();
    // setting the window dimensions
    window->create(sf::VideoMode::getFullscreenModes()[0], "CHESS", sf::Style::Fullscreen);

    makeStates();

    x_state = n_states.at(states::Main_Menu);
}

void Engine::Game::makeStates()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(n_states.empty() == false);
            BOOST_CONTRACT_ASSERT(n_states.size() == 10);
        })
    ;

    x_state = std::make_shared<MainMenu>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<StartMenu>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<FreePlay>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<RapidPlay>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<FritzPlay>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<BulletPlay>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<CustomPlay>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<LearnChess>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<LearnChessb>(window);
    n_states.push_back(std::move(x_state));
    x_state = std::make_shared<About>(window);
    n_states.push_back(std::move(x_state));
}

void Engine::Game::run()
{
    // formatting the sfml pattern
    window->setKeyRepeatEnabled(false);
    window->setFramerateLimit(60);

    while(window->isOpen())
    {
        sf::Event event;
	    while (window->pollEvent(event))
	    {
		    if (event.type == sf::Event::Closed)
		    {
			    window->close();
		    }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window->close();
            x_state->Input(event, x_state, n_states);
        }
        x_state->Logic();
        window->clear(sf::Color::Transparent);
        x_state->Draw();
        window->display();
    }
}