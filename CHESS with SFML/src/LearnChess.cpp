#include "LearnChess.hpp"

LearnChess::LearnChess(std::shared_ptr<sf::RenderWindow> &x_window) : State(x_window), backButton(false),
    nextButton(false)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(backButton == false);
            BOOST_CONTRACT_ASSERT(nextButton == false);
        })
    ;

    Variables();
}

void LearnChess::Variables()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(name.getPosition().x == window->getSize().x / 2);
            BOOST_CONTRACT_ASSERT(name.getPosition().y == name.getLocalBounds().height / 2);
            BOOST_CONTRACT_ASSERT(name.getFillColor() == sf::Color::Red);
            BOOST_CONTRACT_ASSERT(back.getFont() == &data.Pacifico_font);
            BOOST_CONTRACT_ASSERT(back.getString() == "Back");
            BOOST_CONTRACT_ASSERT(back.getPosition().x == 0);
            BOOST_CONTRACT_ASSERT(back.getPosition().y == 0);
        })
    ;
    
    // setting the title
    Set_Text(name, data.Round_Bold, "Rules of CHESS", 0.08 * window->getSize().y, window->getSize().x / 2, 0);
    name.setPosition(window->getSize().x / 2, name.getLocalBounds().height / 2);
    name.setFillColor(sf::Color::Red);

    std::string temp;
    
    // intro
    temp = "2 colours of chess White and black, 6 different coins of chess.\n"
            "It contains 8 Pawns, 2 Knights,2 Rocks, 2 Bishops, 1 King ,1 Queen of each colour.\n"
            "Totally the board contains 16 black coins, 16 White coins. Total=32 coins.\n"
            "It coins alternate White and black grids 32 white ,32 black grids.\n"
            "1.King     2.Queen     3.Bishop     4.Rock     5.Knight     6.Pawn";
    Set_Text(intro, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        0.2 * window->getSize().y);
    intro.setFillColor(sf::Color::Black);

    // King
    Set_Text(King, data.Round_Bold, "King:", 0.03 * window->getSize().y, window->getSize().x / 6,
        intro.getGlobalBounds().height/2 + intro.getPosition().y + 0.02 * window->getSize().y);
    King.setFillColor(sf::Color::Red);
    King.setStyle(sf::Text::Bold);

    temp = "-King can move only one step in any direction.\n"
            "-King is the main coin to be protected until end of game.\n"
            "-It can kill any coin in its way except the opponent king.";
    Set_Text(KingC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        King.getGlobalBounds().height/2 + King.getPosition().y + 0.03 * window->getSize().y);
    KingC.setFillColor(sf::Color::Black);

    // Queen
    Set_Text(Queen, data.Round_Bold, "Queen:", 0.03 * window->getSize().y, window->getSize().x / 6,
        KingC.getGlobalBounds().height/2 + KingC.getPosition().y + 0.03 * window->getSize().y);
    Queen.setFillColor(sf::Color::Red);
    Queen.setStyle(sf::Text::Bold);

    temp = "-Queen is also one of the powerful coins in this game.\n"
            "-It can move any number of steps horizantally,Vertically and diagonally.\n"
            "-It can kill the opponent in its way also it can attack opponent king.";
    Set_Text(QueenC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        Queen.getGlobalBounds().height/2 + Queen.getPosition().y + 0.03 * window->getSize().y);
    QueenC.setFillColor(sf::Color::Black);

    // Bishop
    Set_Text(Bishop, data.Round_Bold, "Bishop:", 0.03 * window->getSize().y, window->getSize().x / 6,
        QueenC.getGlobalBounds().height/2 + QueenC.getPosition().y + 0.03 * window->getSize().y);
    Bishop.setFillColor(sf::Color::Red);
    Bishop.setStyle(sf::Text::Bold);

    temp = "-Bishop can only move diagonally only.\n"
            "-The Bishop placed in white grid can only move diagonally in white grids similarly black.\n"
            "-It can kill the opponent in its way also it can attack opponent king.";
    Set_Text(BishopC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        Bishop.getGlobalBounds().height/2 + Bishop.getPosition().y + 0.03 * window->getSize().y);
    BishopC.setFillColor(sf::Color::Black);

    // Rook
    Set_Text(Rook, data.Round_Bold, "Rook:", 0.03 * window->getSize().y, window->getSize().x / 6,
        BishopC.getGlobalBounds().height/2 + BishopC.getPosition().y + 0.03 * window->getSize().y);
    Rook.setFillColor(sf::Color::Red);
    Rook.setStyle(sf::Text::Bold);

    temp = "-Rock can move any number of steps either horizantally or vertically only.\n"
            "-Rock is also important during castling move.\n"
            "-It can kill the opponent in its way also it can attack opponent king.";
    Set_Text(RookC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        Rook.getGlobalBounds().height/2 + Rook.getPosition().y + 0.03 * window->getSize().y);
    RookC.setFillColor(sf::Color::Black);

    // Knight
    Set_Text(Knight, data.Round_Bold, "Knight:", 0.03 * window->getSize().y, window->getSize().x / 6,
        RookC.getGlobalBounds().height/2 + RookC.getPosition().y + 0.03 * window->getSize().y);
    Knight.setFillColor(sf::Color::Red);
    Knight.setStyle(sf::Text::Bold);

    temp = "-Knight can move 3 steps in L-shape.\n"
            "-Two steps forward horizantally or vertically and one step either to left or right.\n"
            "-It is the only coin that can jump even if there are obstracles between.\n"
            "-It can kill the opponent in its way also it can attack opponent king.";
    Set_Text(KnightC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        Knight.getGlobalBounds().height/2 + Knight.getPosition().y + 0.03 * window->getSize().y);
    KnightC.setFillColor(sf::Color::Black);

    // Pawn
    Set_Text(Pawn, data.Round_Bold, "Pawn:", 0.03 * window->getSize().y, window->getSize().x / 9,
        KnightC.getGlobalBounds().height/2 + KnightC.getPosition().y + 0.03 * window->getSize().y);
    Pawn.setFillColor(sf::Color::Red);
    Pawn.setStyle(sf::Text::Bold);

    temp = "-Pawn can move 1 or 2 steps initially and 1 step in every next move.\n"
            "-It can only move in forward direction in vertical direction only.\n"
            "-It can kill opponent which is placed one step diagonally placed before it also it can attack opponent king.\n"
            "-Pawn when reaches the position of opponent high powers it can be transformed into a higher power other than king.";
    Set_Text(PawnC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        Pawn.getGlobalBounds().height/2 + Pawn.getPosition().y + 0.03 * window->getSize().y);
    PawnC.setFillColor(sf::Color::Black);


    // setting the next button
    next.setFont(data.Pacifico_font);
    next.setString("Next");
    next.setCharacterSize(0.04 * window->getSize().y);
    next.setPosition(0.93 * window->getSize().x, 0);

    // setting the back button
    back.setFont(data.Pacifico_font);
    back.setString("Back");
    back.setCharacterSize(0.04 * window->getSize().y);
    back.setPosition(0, 0);
}

void LearnChess::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function<
        override_Input>(v, &LearnChess::Input, this, event, xState, x_list)
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
        Menu_input(next, nextButton, event);
    }

    if(backButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        xState = x_list.at(Engine::states::Main_Menu);
        backButton = false;
    }
    if(nextButton && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        xState = x_list.at(Engine::states::Learn_Chessb);
        nextButton = false;
    }
}

void LearnChess::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Logic>(v, &LearnChess::Logic, this);

    Highlight_options(backButton, back);
    Highlight_options(nextButton, next);
}

void LearnChess::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Draw>(v, &LearnChess::Draw, this);

    window->draw(backGround);
    window->draw(name);
    window->draw(intro);
    window->draw(King);
    window->draw(KingC);
    window->draw(Queen);
    window->draw(QueenC);
    window->draw(Bishop);
    window->draw(BishopC);
    window->draw(Rook);
    window->draw(RookC);
    window->draw(Knight);
    window->draw(KnightC);
    window->draw(Pawn);
    window->draw(PawnC);
    window->draw(next);
    window->draw(back);
}