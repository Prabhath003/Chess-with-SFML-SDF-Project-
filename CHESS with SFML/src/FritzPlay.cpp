#include "FritzPlay.hpp"

FritzPlay::FritzPlay(std::shared_ptr<sf::RenderWindow> &x_window) : GameType(x_window)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
        })
    ;

    Variables();
}

void FritzPlay::Variables()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(name.getPosition().x == window->getSize().x / 2);
            BOOST_CONTRACT_ASSERT(name.getPosition().y == name.getLocalBounds().height / 2);
            BOOST_CONTRACT_ASSERT(name.getFillColor() == sf::Color::Red);
            BOOST_CONTRACT_ASSERT(setTotalTime >= 10);
            BOOST_CONTRACT_ASSERT(setTotalTime == 420);
            BOOST_CONTRACT_ASSERT(firstTime == false);
        })
    ;

    // setting the title
    Set_Text(name, data.Round_Bold, "Fritz Play", 0.08 * window->getSize().y, window->getSize().x / 2, 0);
    name.setPosition(window->getSize().x / 2, name.getLocalBounds().height / 2);
    name.setFillColor(sf::Color::Red);

    setTotalTime = 7 * 60;
    firstTime = false;
}

void FritzPlay::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function<
        override_Input>(v, &FritzPlay::Input, this, event, xState, x_list)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(x_list.size() == old_list->size());
            for(unsigned i = 0; i < old_list->size(); i++)
            {
                BOOST_CONTRACT_ASSERT(x_list.at(i) == old_list->at(i));
            }
        })
    ;

    GameType::Input(event, xState, x_list);
}

void FritzPlay::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Logic>(v, &FritzPlay::Logic, this);

    GameType::Logic();
}

void FritzPlay::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Draw>(v, &FritzPlay::Draw, this);

    GameType::Draw();
}