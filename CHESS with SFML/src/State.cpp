#include "State.hpp"

Engine::State::State(std::shared_ptr<sf::RenderWindow> &x_window)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] { // postconditon checks
            BOOST_CONTRACT_ASSERT(window != nullptr);
        })
    ;
    
    if(window == nullptr)
    {
        window = x_window;
    }

    Variables();
}

void Engine::State::Variables()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(backGround.getSize().x == window->getSize().x);
            BOOST_CONTRACT_ASSERT(backGround.getSize().x == window->getSize().x);
            BOOST_CONTRACT_ASSERT(backGround.getPosition().x == 0);
            BOOST_CONTRACT_ASSERT(backGround.getPosition().y == 0);
            BOOST_CONTRACT_ASSERT(backGround.getTexture() == &data.tex_BackGround);
            BOOST_CONTRACT_ASSERT(min == 0);
            BOOST_CONTRACT_ASSERT(hr == 0);
            BOOST_CONTRACT_ASSERT(sec == 0);
            BOOST_CONTRACT_ASSERT(time.getFillColor() == sf::Color::Green);
        })
    ;

    // initializing the time variables
    min = 0;
    hr = 0;
    sec = 0;
    timecountsec = std::chrono::steady_clock::duration::zero();

    // setting the time
    tempTime = "Time: \n " + std::to_string(hr) + " : " + std::to_string(min) + " : " + std::to_string(sec);
    Set_Text(time, data.Round_Bold, tempTime, 0.08 * window->getSize().y, window->getSize().x / 6,
        4 * window->getSize().y / 5);
    time.setFillColor(sf::Color::Green);

    // setting background
    backGround.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    backGround.setPosition(0, 0);
    backGround.setTexture(&data.tex_BackGround);
}

void Engine::State::Set_Text(sf::Text &name, sf::Font &tex, std::string s, size_t character_size,
    float pos_x, float pos_y)
{
    boost::contract::old_ptr<std::string> old_s = BOOST_CONTRACT_OLDOF(s);
    boost::contract::old_ptr<size_t> old_character_size = BOOST_CONTRACT_OLDOF(character_size);
    boost::contract::old_ptr<float> old_pos_x = BOOST_CONTRACT_OLDOF(pos_x);
    boost::contract::old_ptr<float> old_pos_y = BOOST_CONTRACT_OLDOF(pos_y);
    boost::contract::check c = boost::contract::function()
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(s.empty() == false);
            BOOST_CONTRACT_ASSERT(pos_x >= 0);
            BOOST_CONTRACT_ASSERT(pos_y >= 0);
        })
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(s == *old_s);
            BOOST_CONTRACT_ASSERT(character_size == *old_character_size);
            BOOST_CONTRACT_ASSERT(pos_x == *old_pos_x);
            BOOST_CONTRACT_ASSERT(pos_y == *old_pos_y);
            BOOST_CONTRACT_ASSERT(name.getCharacterSize() == character_size);
            BOOST_CONTRACT_ASSERT(name.getPosition().x >= 0);
            BOOST_CONTRACT_ASSERT(name.getPosition().y >= 0);
            BOOST_CONTRACT_ASSERT(name.getPosition().x == pos_x);
            BOOST_CONTRACT_ASSERT(name.getPosition().y == pos_y);
            BOOST_CONTRACT_ASSERT(name.getString() == s);
            BOOST_CONTRACT_ASSERT(name.getFont() == &tex);
        })
    ;

    name.setFont(tex);
    name.setString(s);
    name.setCharacterSize(character_size);
    name.setOrigin(name.getLocalBounds().width / 2,
        name.getLocalBounds().height / 2);
    name.setPosition(pos_x, pos_y);
}

void Engine::State::Menu_input(sf::Text &name, bool &button, sf::Event &event)
{
    boost::contract::old_ptr<sf::Text> old_name = BOOST_CONTRACT_OLDOF(name);
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(name.getCharacterSize() == old_name->getCharacterSize());
            BOOST_CONTRACT_ASSERT(name.getPosition().x == old_name->getPosition().x);
            BOOST_CONTRACT_ASSERT(name.getPosition().y == old_name->getPosition().y);
            BOOST_CONTRACT_ASSERT(name.getString() == old_name->getString());
            BOOST_CONTRACT_ASSERT(name.getFont() == old_name->getFont());
        })
    ;

    button = name.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y) ? true : false;
}

void Engine::State::Highlight_options(bool &button, sf::Text &name)
{
    boost::contract::old_ptr<bool> old_button = BOOST_CONTRACT_OLDOF(button);
    boost::contract::old_ptr<sf::Text> old_name = BOOST_CONTRACT_OLDOF(name);
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(button == *old_button);
            BOOST_CONTRACT_ASSERT(name.getCharacterSize() == old_name->getCharacterSize());
            BOOST_CONTRACT_ASSERT(name.getPosition().x == old_name->getPosition().x);
            BOOST_CONTRACT_ASSERT(name.getPosition().y == old_name->getPosition().y);
            BOOST_CONTRACT_ASSERT(name.getString() == old_name->getString());
            BOOST_CONTRACT_ASSERT(name.getFont() == old_name->getFont());
            if(button == true)
                BOOST_CONTRACT_ASSERT(name.getFillColor() == sf::Color::Magenta);
            if(button == false)
                BOOST_CONTRACT_ASSERT(name.getFillColor() == sf::Color::Blue);
        })
    ;
    
    if(button)
        name.setFillColor(sf::Color::Magenta);
    else
        name.setFillColor(sf::Color::Blue);
}


// function to calculate the time passed
void Engine::State::calculateTime()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(hr >= 0);
            BOOST_CONTRACT_ASSERT(min >= 0);
            BOOST_CONTRACT_ASSERT(sec >= 0);
            BOOST_CONTRACT_ASSERT(time.getString().isEmpty() == false);
        })
    ;

    end = std::chrono::steady_clock::now();
    timecountsec += end - start;
    start = std::chrono::steady_clock::now();
    int temp = timecountsec.count();
    hr = temp / 3600;
    min = temp % 3600 / 60;
    sec = temp % 3600 % 60;
    tempTime = "Time: \n " + std::to_string(hr) + " : " + std::to_string(min) + " : " + std::to_string(sec);
    time.setString(tempTime);
}

void Engine::State::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function(v, this)
        .precondition([&] {
            BOOST_CONTRACT_ASSERT(x_list.empty() == false);
        })
    ;
}

void Engine::State::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function(v, this);
    assert(false);
}

void Engine::State::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function(v, this);
    assert(false);
}