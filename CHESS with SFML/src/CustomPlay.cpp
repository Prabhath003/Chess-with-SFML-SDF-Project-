#include "CustomPlay.hpp"

CustomPlay::CustomPlay(std::shared_ptr<sf::RenderWindow> &x_window) : GameType(x_window)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
        })
    ;

    Variables();
}

void CustomPlay::Variables()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(name.getPosition().x == window->getSize().x / 2);
            BOOST_CONTRACT_ASSERT(name.getPosition().y == name.getLocalBounds().height / 2);
            BOOST_CONTRACT_ASSERT(name.getFillColor() == sf::Color::Red);
            BOOST_CONTRACT_ASSERT(operate == false);
            BOOST_CONTRACT_ASSERT(setTime.getFillColor() == sf::Color::Green);
            BOOST_CONTRACT_ASSERT(setTime.getStyle() == sf::Text::Bold);
            BOOST_CONTRACT_ASSERT(replay.getString() == "Play");
            BOOST_CONTRACT_ASSERT(uparrow.getTexture() == downarrow.getTexture());
            BOOST_CONTRACT_ASSERT(uparrow.getTexture() == &data.tex_arrow);
            BOOST_CONTRACT_ASSERT(downarrow.getRotation() - uparrow.getRotation() == 180);
            BOOST_CONTRACT_ASSERT(uparrow.getSize().x == downarrow.getSize().x);
            BOOST_CONTRACT_ASSERT(uparrow.getSize().y == downarrow.getSize().y);
            BOOST_CONTRACT_ASSERT(uparrow.getSize().y == uparrow.getSize().x);
            BOOST_CONTRACT_ASSERT(uparrow.getPosition().y == downarrow.getPosition().y);
        })
    ;

    operate = false;

    // setting the title
    Set_Text(name, data.Round_Bold, "Custom Play", 0.08 * window->getSize().y, window->getSize().x / 2, 0);
    name.setPosition(window->getSize().x / 2, name.getLocalBounds().height / 2);
    name.setFillColor(sf::Color::Red);

    replay.setString("Play");

    Set_Text(setTime, data.Round_Bold, "Time: 0 : 0 : 10", 0.04 * window->getSize().y, backscreen.getPosition().x,
        backscreen.getPosition().y + 2.5 * backscreen.getSize().y / 6);
    setTime.setFillColor(sf::Color::Green);
    setTime.setStyle(sf::Text::Bold);

    uparrow.setTexture(&data.tex_arrow);
    uparrow.setSize(sf::Vector2f(0.04 * window->getSize().y, 0.04 * window->getSize().y));
    uparrow.setOrigin(uparrow.getLocalBounds().width / 2,
        uparrow.getLocalBounds().height / 2);
    uparrow.setPosition(backscreen.getPosition().x + backscreen.getSize().x / 6,
        backscreen.getPosition().y + 2.5 * backscreen.getSize().y / 6);

    downarrow.setTexture(&data.tex_arrow);
    downarrow.rotate(180);
    downarrow.setSize(sf::Vector2f(0.04 * window->getSize().y, 0.04 * window->getSize().y));
    downarrow.setOrigin(downarrow.getLocalBounds().width / 2,
        downarrow.getLocalBounds().height / 2);
    downarrow.setPosition(backscreen.getPosition().x - backscreen.getSize().x / 6,
        backscreen.getPosition().y + 2.5 * backscreen.getSize().y / 6);
}

void CustomPlay::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function<
        override_Input>(v, &CustomPlay::Input, this, event, xState, x_list)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(x_list.size() == old_list->size());
            for(unsigned i = 0; i < old_list->size(); i++)
            {
                BOOST_CONTRACT_ASSERT(x_list.at(i) == old_list->at(i));
            }
        })
    ;

    GameType::Input(event, xState, x_list);

    if(game->reset(event))
    {
        operate = false;
    }

    if(!operate)
    {
        if(event.type == sf::Event::MouseMoved)
        {
            upbutton = uparrow.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y) ? true : false;
            downbutton = downarrow.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y) ? true : false;
        }
        if(upbutton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            setTotalTime++;
        if(downbutton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(setTotalTime > 10)
                setTotalTime--;
        }
    }
}

void CustomPlay::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Logic>(v, &CustomPlay::Logic, this);

    GameType::Logic();

    setTime.setString("Time: " + std::to_string(sethr) + " : " + std::to_string(setmin) + " : " + std::to_string(setsec));
}

void CustomPlay::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Draw>(v, &CustomPlay::Draw, this);
    
    GameType::Draw();
}