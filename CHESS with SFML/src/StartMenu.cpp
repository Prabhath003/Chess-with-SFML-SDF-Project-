#include "StartMenu.hpp"

StartMenu::StartMenu(std::shared_ptr<sf::RenderWindow> &x_window) : State(x_window),
    freeButton(false), rapidButton(false), fritzButton(false),
    bulletButton(false), customButton(false), backButton(false)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(freeButton == false);
            BOOST_CONTRACT_ASSERT(rapidButton == false);
            BOOST_CONTRACT_ASSERT(fritzButton == false);
            BOOST_CONTRACT_ASSERT(bulletButton == false);
            BOOST_CONTRACT_ASSERT(customButton == false);
            BOOST_CONTRACT_ASSERT(backButton == false);
        })
    ;

    Variables();
}

void StartMenu::Variables()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(back.getFont() == &data.Pacifico_font);
            BOOST_CONTRACT_ASSERT(back.getString() == "Back");
            BOOST_CONTRACT_ASSERT(back.getPosition().x == 0);
            BOOST_CONTRACT_ASSERT(back.getPosition().y == 0);
        })
    ;

    // setting freePlay text
    Set_Text(free, data.Pacifico_font, "Free Play", 0.08 * window->getSize().y, window->getSize().x / 2,
        window->getSize().y / 2 - 0.25 * window->getSize().y);
    // setting RapidPlay text
    Set_Text(rapid, data.Pacifico_font, "Rapid Play", 0.08 * window->getSize().y, window->getSize().x / 2,
        window->getSize().y / 2 - 0.15 * window->getSize().y);
    // setting FritzPlay text
    Set_Text(fritz, data.Pacifico_font, "Fritz Play", 0.08 * window->getSize().y, window->getSize().x / 2, 
        window->getSize().y / 2 - 0.05 * window->getSize().y);
    // setting BulletPlay text
    Set_Text(bullet, data.Pacifico_font, "Bullet Play", 0.08 * window->getSize().y, window->getSize().x / 2,
        window->getSize().y / 2 + 0.05 * window->getSize().y);
    // setting Custom Text
    Set_Text(custom, data.Pacifico_font, "Custom Play", 0.08 * window->getSize().y, window->getSize().x / 2,
        window->getSize().y / 2 + 0.15 * window->getSize().y);
    
    // setting Back text
    back.setFont(data.Pacifico_font);
    back.setString("Back");
    back.setCharacterSize(0.04 * window->getSize().y);
    back.setPosition(0, 0);
}

void StartMenu::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function<
        override_Input>(v, &StartMenu::Input, this, event, xState, x_list)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(x_list.size() == old_list->size());
            for(unsigned i = 0; i < old_list->size(); i++)
            {
                BOOST_CONTRACT_ASSERT(x_list.at(i) == old_list->at(i));
            }
        })
    ;

        if(event.type == sf::Event::MouseMoved)
        {
            Menu_input(free, freeButton, event);
            Menu_input(rapid, rapidButton, event);
            Menu_input(fritz, fritzButton, event);
            Menu_input(bullet, bulletButton, event);
            Menu_input(custom, customButton, event);
            Menu_input(back, backButton, event);
        }

        if(backButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            xState = x_list.at(Engine::states::Main_Menu);
            backButton = false;
        }
        if(freeButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            xState = x_list.at(Engine::states::Free_Play);
            x_list.at(Engine::states::Free_Play)->start = std::chrono::steady_clock::now();
            freeButton = false;
        }
        if(rapidButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            xState = x_list.at(Engine::states::Rapid_Play);
            x_list.at(Engine::states::Rapid_Play)->start = std::chrono::steady_clock::now();
            rapidButton = false;
        }
        if(fritzButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            xState = x_list.at(Engine::states::Fritz_Play);
            x_list.at(Engine::states::Fritz_Play)->start = std::chrono::steady_clock::now();
            fritzButton = false;
        }
        if(bulletButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            xState = x_list.at(Engine::states::Bullet_Play);
            x_list.at(Engine::states::Bullet_Play)->start = std::chrono::steady_clock::now();
            bulletButton = false;
        }
        if(customButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            xState = x_list.at(Engine::states::Custom_Play);
            x_list.at(Engine::states::Free_Play)->start = std::chrono::steady_clock::now();
            customButton = false;
        }
}

void StartMenu::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Logic>(v, &StartMenu::Logic, this);

    Highlight_options(freeButton, free);
    Highlight_options(rapidButton, rapid);
    Highlight_options(fritzButton, fritz);
    Highlight_options(bulletButton, bullet);
    Highlight_options(customButton, custom);
    Highlight_options(backButton, back);
}

void StartMenu::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Draw>(v, &StartMenu::Draw, this);

    window->draw(backGround);
    window->draw(free);
    window->draw(rapid);
    window->draw(fritz);
    window->draw(bullet);
    window->draw(custom);
    window->draw(back);
}