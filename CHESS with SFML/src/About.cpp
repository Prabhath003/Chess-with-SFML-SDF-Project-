#include "About.hpp"

About::About(std::shared_ptr<sf::RenderWindow> &x_window) : State(x_window), backButton(false)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(backButton == false);
        })
    ;

    Variables();
}

void About::Variables()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(back.getFont() == &data.Pacifico_font);
            BOOST_CONTRACT_ASSERT(back.getString() == "Back");
            BOOST_CONTRACT_ASSERT(back.getPosition().x == 0);
            BOOST_CONTRACT_ASSERT(back.getPosition().y == 0);
            BOOST_CONTRACT_ASSERT(name.getPosition().x == window->getSize().x / 2);
            BOOST_CONTRACT_ASSERT(name.getPosition().y == name.getLocalBounds().height / 2);
            BOOST_CONTRACT_ASSERT(name.getFillColor() == sf::Color::Red);
            BOOST_CONTRACT_ASSERT(Types.getFillColor() == sf::Color::Green);
            BOOST_CONTRACT_ASSERT(Types.getStyle() == sf::Text::Bold);
        })
    ;

    // setting the title
    Set_Text(name, data.Round_Bold, "About", 0.08 * window->getSize().y, window->getSize().x / 2, 0);
    name.setPosition(window->getSize().x / 2, name.getLocalBounds().height / 2);
    name.setFillColor(sf::Color::Red);

    std::string temp;

    temp = "1. Bullet Play -> 1.5 minutes\n"
            "2. Fritz Play -> 7 minutes\n"
            "3. Rapid Play -> 35 minutes\n"
            "4. Free Play -> no time limit\n"
            "5. Custom Play -> time can be set";
    Set_Text(Types, data.Round_Bold, temp, 0.08 * window->getSize().y, window->getSize().x / 2, window->getSize().y / 2);
    Types.setFillColor(sf::Color::Green);
    Types.setStyle(sf::Text::Bold);

    back.setFont(data.Pacifico_font);
    back.setString("Back");
    back.setCharacterSize(0.04 * window->getSize().y);
    back.setPosition(0, 0);
}

void About::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function<
        override_Input>(v, &About::Input, this, event, xState, x_list)
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
        Menu_input(back, backButton, event);
    }

    if(backButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        xState = x_list.at(Engine::states::Main_Menu);
        backButton = false;
    }
}

void About::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Logic>(v, &About::Logic, this);

    Highlight_options(backButton, back);
}

void About::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Draw>(v, &About::Draw, this);

    window->draw(backGround);
    window->draw(name);
    window->draw(Types);
    window->draw(back);
}