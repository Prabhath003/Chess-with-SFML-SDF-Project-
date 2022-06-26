#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<sf::RenderWindow> &x_window) : State(x_window),
    startButton(false), learnChessButton(false), aboutButton(false), exitButton(false)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(startButton == false);
            BOOST_CONTRACT_ASSERT(learnChessButton == false);
            BOOST_CONTRACT_ASSERT(aboutButton == false);
            BOOST_CONTRACT_ASSERT(exitButton == false);
        })
    ;

    Variables();
}

void MainMenu::Variables()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(title.getFillColor() == sf::Color::Red);
        })
    ;

    // setting title
    Set_Text(title, data.Beams_font, "CHESS", 0.2 * window->getSize().y, window->getSize().x / 2,
        window->getSize().y / 4);
    title.setFillColor(sf::Color::Red);

    // setting Start text
    Set_Text(start, data.Pacifico_font, "Start", 0.08 * window->getSize().y, window->getSize().x / 2,
        window->getSize().y / 2);  
    // setting LearnChess text
    Set_Text(learnChess, data.Pacifico_font, "Learn Chess", 0.08 * window->getSize().y, window->getSize().x / 2,
        window->getSize().y / 2 + 0.1 * window->getSize().y);
    // setting About text
    Set_Text(about, data.Pacifico_font, "About", 0.08 * window->getSize().y, window->getSize().x / 2,
        window->getSize().y / 2 + 0.2 * window->getSize().y);
    // setting Exit text
    Set_Text(exit, data.Pacifico_font, "Exit", 0.08 * window->getSize().y, window->getSize().x / 2, 
        window->getSize().y / 2 + 0.3 * window->getSize().y);
}

void MainMenu::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function<
        override_Input>(v, &MainMenu::Input, this, event, xState, x_list)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(x_list.size() == old_list->size());
            for(unsigned i = 0; i < old_list->size(); i++)
            {
                BOOST_CONTRACT_ASSERT(x_list.at(i) == old_list->at(i));
            }
        })
    ;

    // receving input from the user
    if(event.type == sf::Event::MouseMoved)
    {
        Menu_input(start, startButton, event);
        Menu_input(learnChess, learnChessButton, event);
        Menu_input(about, aboutButton, event);
        Menu_input(exit, exitButton, event);
    }

    if(exitButton && sf::Mouse::isButtonPressed(sf::Mouse::Left)) window->close();
    if(startButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        xState = x_list.at(Engine::states::Start_Menu);
        startButton = false;
    }
    if(learnChessButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        xState = x_list.at(Engine::states::Learn_Chess);
        learnChessButton = false;
    }
    if(aboutButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        xState = x_list.at(Engine::states::about);
        aboutButton = false;
    }
}

void MainMenu::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Logic>(v, &MainMenu::Logic, this)
        .postcondition([&] {
            if(startButton == true)
                BOOST_CONTRACT_ASSERT(start.getFillColor() == sf::Color::Magenta);
            else
                BOOST_CONTRACT_ASSERT(start.getFillColor() == sf::Color::Blue);
            if(learnChessButton == true)
                BOOST_CONTRACT_ASSERT(learnChess.getFillColor() == sf::Color::Magenta);
            else
                BOOST_CONTRACT_ASSERT(learnChess.getFillColor() == sf::Color::Blue);
            if(exitButton == true)
                BOOST_CONTRACT_ASSERT(exit.getFillColor() == sf::Color::Magenta);
            else
                BOOST_CONTRACT_ASSERT(exit.getFillColor() == sf::Color::Blue);
        })
    ;
    Highlight_options(startButton, start);
    Highlight_options(learnChessButton, learnChess);
    Highlight_options(aboutButton, about);
    Highlight_options(exitButton, exit);
    // checking the bool operators performing related tasks
}

void MainMenu::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Draw>(v, &MainMenu::Draw, this);

    window->draw(backGround);
    window->draw(title);
    window->draw(start);
    window->draw(learnChess);
    window->draw(about);
    window->draw(exit);
}