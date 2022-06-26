#include "LearnChessb.hpp"

LearnChessb::LearnChessb(std::shared_ptr<sf::RenderWindow> &x_window) : State(x_window), backButton(false)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(backButton == false);
        })
    ;

    Variables();
}

void LearnChessb::Variables()
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
    
    // note
    temp = "Note\n"
"Except the Knight no other coin can jump if there are obstracles.";
    Set_Text(note, data.Round_Bold, temp, 0.03 * window->getSize().y, window->getSize().x / 2,
        0.2 * window->getSize().y);
    note.setFillColor(sf::Color::Black);

    // Special
    temp = "Special moves:\n"
 "1.Castling move   2.En Pasant move.";
    Set_Text(special, data.Round_Bold, temp, 0.03 * window->getSize().y, window->getSize().x / 2,
        note.getGlobalBounds().height/2 + note.getPosition().y + 0.05 * window->getSize().y);
    special.setFillColor(sf::Color::Black);

    // castling
    Set_Text(castling, data.Round_Bold, "Castling:", 0.03 * window->getSize().y, window->getSize().x / 6,
        special.getGlobalBounds().height/2 + special.getPosition().y + 0.04 * window->getSize().y);
    castling.setFillColor(sf::Color::Red);
    castling.setStyle(sf::Text::Bold);

    temp = "-This move is possible when the king and Rock of same color lie in same line.\n"
 "-This move should be taken when no other coins lie in between King and Rock.\n"
 "-In this move The king should move to the side of Rock with which it want to castle by one step.\n"
 "-Then the Rock movess to the other side of king (next vacant grid to king)";
    Set_Text(castlingC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        castling.getGlobalBounds().height/2 + castling.getPosition().y + 0.04 * window->getSize().y);
    castlingC.setFillColor(sf::Color::Black);

    // enPassant
    Set_Text(enPassant, data.Round_Bold, "EnPassant:", 0.03 * window->getSize().y, window->getSize().x / 6,
        castlingC.getGlobalBounds().height/2 + castlingC.getPosition().y + 0.04 * window->getSize().y);
    enPassant.setFillColor(sf::Color::Red);
    enPassant.setStyle(sf::Text::Bold);

    temp = "This rule holds when the Pawn initially moves two steps  in first move and reaches the adjacent side of opponent\n"
 "-Then the opponent can capture this Pawn and move a step foeward.\n"
 "-This move should be taken immediately after the Pawn reaches its side. Else it is not Valid.";
    Set_Text(enPassantC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        enPassant.getGlobalBounds().height/2 + enPassant.getPosition().y + 0.04 * window->getSize().y);
    enPassantC.setFillColor(sf::Color::Black);

    // check
    Set_Text(check, data.Round_Bold, "Check:", 0.03 * window->getSize().y, window->getSize().x / 6,
        enPassantC.getGlobalBounds().height/2 + enPassantC.getPosition().y + 0.04 * window->getSize().y);
    check.setFillColor(sf::Color::Red);
    check.setStyle(sf::Text::Bold);

    temp = "-The main aim of the game is to attack the opponent King.\n"
 "-The King is said to be in check if any opponent has chance to attack king in next move.\n"
 "-In such case The King has to be protected by moving to the place where there is no chance of attack (in one step).";
    Set_Text(checkC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        check.getGlobalBounds().height/2 + check.getPosition().y + 0.04 * window->getSize().y);
    checkC.setFillColor(sf::Color::Black);

    // mate
    Set_Text(mate, data.Round_Bold, "CheckMate:", 0.03 * window->getSize().y, window->getSize().x / 6,
        checkC.getGlobalBounds().height/2 + checkC.getPosition().y + 0.04 * window->getSize().y);
    mate.setFillColor(sf::Color::Red);
    mate.setStyle(sf::Text::Bold);

    temp = "-The king is said to be in checkmate if all secure places are under attack of opponent and King has no way to move.\n"
 "-If The King is in checkmate then the opponent is declared as a winner.";
    Set_Text(mateC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        mate.getGlobalBounds().height/2 + mate.getPosition().y + 0.04 * window->getSize().y);
    mateC.setFillColor(sf::Color::Black);

    // draw
    Set_Text(draw, data.Round_Bold, "Draw:", 0.03 * window->getSize().y, window->getSize().x / 6,
        mateC.getGlobalBounds().height/2 + mateC.getPosition().y + 0.04 * window->getSize().y);
    draw.setFillColor(sf::Color::Red);
    draw.setStyle(sf::Text::Bold);

    temp = "- A game is said to be draw if none of the players have any legal moves to capture opponent King.\n"
 "-This is also described as stalemate.";
    Set_Text(drawC, data.Round_Bold, temp, 0.02 * window->getSize().y, window->getSize().x / 2,
        draw.getGlobalBounds().height/2 + draw.getPosition().y + 0.04 * window->getSize().y);
    drawC.setFillColor(sf::Color::Black);

    back.setFont(data.Pacifico_font);
    back.setString("Back");
    back.setCharacterSize(0.04 * window->getSize().y);
    back.setPosition(0, 0);
}

void LearnChessb::Input(sf::Event &event, std::shared_ptr<State> &xState,
    std::vector<std::shared_ptr<State>> &x_list, boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<std::vector<std::shared_ptr<State>>> old_list = BOOST_CONTRACT_OLDOF(x_list);
    boost::contract::check c = boost::contract::public_function<
        override_Input>(v, &LearnChessb::Input, this, event, xState, x_list)
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
        xState = x_list.at(Engine::states::Learn_Chess);
        backButton = false;
    }
}

void LearnChessb::Logic(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Logic>(v, &LearnChessb::Logic, this);

    Highlight_options(backButton, back);
}

void LearnChessb::Draw(boost::contract::virtual_ *v)
{
    boost::contract::check c = boost::contract::public_function<
        override_Draw>(v, &LearnChessb::Draw, this);

    window->draw(backGround);
    window->draw(name);
    window->draw(note);
    window->draw(special);
    window->draw(castling);
    window->draw(castlingC);
    window->draw(enPassant);
    window->draw(enPassantC);
    window->draw(check);
    window->draw(checkC);
    window->draw(mate);
    window->draw(mateC);
    window->draw(draw);
    window->draw(drawC);
    window->draw(back);
}