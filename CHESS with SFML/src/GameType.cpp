#include "GameType.hpp"

GameType::GameType(std::shared_ptr<sf::RenderWindow> &x_window) : State(x_window), backButton(false),
    operate(true), replayButton(false), timeLimit(true), firstTime(true), highLightMoves(true),
    showMovesButton(false)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(backButton == false);
            BOOST_CONTRACT_ASSERT(operate == true);
            BOOST_CONTRACT_ASSERT(replayButton == false);
            BOOST_CONTRACT_ASSERT(timeLimit == true);
            BOOST_CONTRACT_ASSERT(firstTime == true);
            BOOST_CONTRACT_ASSERT(highLightMoves == true);
            BOOST_CONTRACT_ASSERT(showMovesButton == false);
        })
    ;

    Variables();
}

void GameType::Variables()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(back.getFont() == &data.Pacifico_font);
            BOOST_CONTRACT_ASSERT(back.getString() == "Back");
            BOOST_CONTRACT_ASSERT(back.getPosition().x == 0);
            BOOST_CONTRACT_ASSERT(back.getPosition().y == 0);
            BOOST_CONTRACT_ASSERT(game != nullptr);
            BOOST_CONTRACT_ASSERT(sethr == 0);
            BOOST_CONTRACT_ASSERT(setmin == 0);
            BOOST_CONTRACT_ASSERT(setsec == 0);
            BOOST_CONTRACT_ASSERT(setTotalTime >= 10);
            BOOST_CONTRACT_ASSERT(showMoves.getFont() == &data.Round_Bold);
            BOOST_CONTRACT_ASSERT(showMoves.getString() == "Show Possible Moves");
        })
    ;

    game = new GameControl(window);

    sethr = 0; setmin = 0; setsec = 0; setTotalTime = 10;

    purpose.setFont(data.Round_Bold);
    winner.setFont(data.Round_Bold);
    purpose.setString("...");
    winner.setString("...");

    backscreen.setSize(sf::Vector2f(4 * window->getSize().x / 5, 2 * window->getSize().y / 3));
    backscreen.setOrigin(backscreen.getLocalBounds().width / 2,
        backscreen.getLocalBounds().height / 2);
    backscreen.setFillColor(sf::Color(255, 0, 0, 100));
    backscreen.setPosition(window->getSize().x / 2, window->getSize().y / 2);
    backscreen.setOutlineColor(sf::Color::Yellow);
    backscreen.setOutlineThickness(0.05 * window->getSize().y);

    Set_Text(replay, data.Round_Bold, "Replay", 0.06 * window->getSize().y, backscreen.getPosition().x,
        backscreen.getPosition().y + window->getSize().y / 8);

    showMoves.setFont(data.Round_Bold);
    showMoves.setString("Show Possible Moves");
    showMoves.setCharacterSize(0.06 * window->getSize().y);
    showMoves.setPosition(0.6 * window->getSize().x, 0.92 * window->getSize().y);

    On.setRadius(0.03 * window->getSize().y);
    On.setOrigin(On.getLocalBounds().width / 2, On.getLocalBounds().height / 2);
    On.setPosition(showMoves.getPosition().x - 0.03 * window->getSize().y,
        showMoves.getPosition().y + 0.03 * window->getSize().y);

    back.setFont(data.Pacifico_font);
    back.setString("Back");
    back.setCharacterSize(0.04 * window->getSize().y);
    back.setPosition(0, 0);
}

void GameType::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function<
        override_Input>(v, &GameType::Input, this, event, xState, x_list);

    if(operate)
    {
        game->runAlgo(event);
        if(game->reset(event))
            timecountsec = std::chrono::steady_clock::duration::zero();
    }
        
    if(event.type == sf::Event::MouseMoved)
    {
        Menu_input(back, backButton, event);
        Menu_input(showMoves, showMovesButton, event);
    }
    if(backButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        xState = x_list.at(Engine::states::Start_Menu);
        backButton = false;
    }
    if(showMovesButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        game->getchess()->toggleHighlightMoves(!highLightMoves);
        highLightMoves = !highLightMoves;
    }

    if(!operate)
    {
        if(event.type == sf::Event::MouseMoved)
        {
            if(setTotalTime > 10)
                Menu_input(replay, replayButton, event);
            else replayButton = false;
        }
        if(replayButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            operate = true;
            timecountsec = std::chrono::steady_clock::duration::zero();
            start = std::chrono::steady_clock::now();
            game->getchess()->restart();
            replayButton = false;
            firstTime = false;
            replay.setString("Replay");
        }
    }
}

void GameType::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Logic>(v, &GameType::Logic, this);

    Highlight_options(backButton, back);
    Highlight_options(showMovesButton, showMoves);
    if(highLightMoves)
    {
        On.setFillColor(sf::Color::Black);
        On.setOutlineColor(sf::Color::Green);
        On.setOutlineThickness(-15.f);
    }
    else
    {
        On.setFillColor(sf::Color::Green);
        On.setOutlineThickness(0);
    }

    if(operate)
        calculateTime();

    sethr = setTotalTime / 3600;
    setmin = setTotalTime % 3600 / 60;
    setsec = setTotalTime % 3600 % 60;

    if(game->getchess()->getWinner() != 2)
    {
        operate = false;
        if(game->getchess()->getWinner() == 1)
        {
            purpose.setString("Check Mate!");
            winner.setString("WHITE is the WINNER...");
        }
        else if(game->getchess()->getWinner() == -1)
        {
            purpose.setString("Check Mate!");
            winner.setString("BLACK is the WINNER...");
        }
        else if(game->getchess()->getWinner() == 0)
        {
            purpose.setString("Stall Mate!");
            winner.setString("It's a DRAW...");
        }
    }
    else if(hr >= sethr && min >= setmin && sec >= setsec && timeLimit)
    {
        operate = false;
        if(firstTime == false)
        {
            purpose.setString("TimeUp!");
            if(game->getchess()->getBlackScore() > game->getchess()->getWhiteScore())
            {
                winner.setString("BLACK is the WINNER...\n");
            }
            else if(game->getchess()->getBlackScore() < game->getchess()->getWhiteScore())
            {
                winner.setString("WHITE is the WINNER...\n");
            }
            else
            {
                winner.setString("It's a DRAW...");
            }
        }
    }

    if(firstTime == true)
        purpose.setString("Select Time\ngreater than 10");

    if(!operate)
    {
        purpose.setCharacterSize(0.08 * window->getSize().y);
        purpose.setOrigin(purpose.getLocalBounds().width / 2,
            purpose.getLocalBounds().height / 2);
        purpose.setPosition(backscreen.getPosition().x, backscreen.getPosition().y - 2 * backscreen.getSize().y / 6);
        purpose.setFillColor(sf::Color::Green);

        winner.setCharacterSize(0.08 * window->getSize().y);
        winner.setOrigin(winner.getLocalBounds().width / 2,
            winner.getLocalBounds().height / 2);
        winner.setPosition(backscreen.getPosition().x, backscreen.getPosition().y);
        winner.setFillColor(sf::Color::Green);

        Highlight_options(replayButton, replay);
    }
}

void GameType::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Draw>(v, &GameType::Draw, this);

    window->draw(backGround);
    window->draw(back);
    window->draw(time);
    window->draw(name);
    game->draw();
    window->draw(showMoves);
    window->draw(On);
    if(!operate)
    {
        window->draw(backscreen);
        window->draw(purpose);
        window->draw(winner);
        window->draw(setTime);
        window->draw(uparrow);
        window->draw(downarrow);
        window->draw(replay);
    }
}

int GameType::getTimeLimit()
{
    return setTotalTime;
}