#include "Algo.hpp"

ChessGame::ChessGame(std::shared_ptr<sf::RenderWindow> &x_window, sf::Color bordCol1, sf::Color bordCol2)
    : window(x_window), board(x_window, bordCol1, bordCol2), winner(2), highlightMoves(true)
{
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] { // postconditon checks
            BOOST_CONTRACT_ASSERT(window != nullptr);
            BOOST_CONTRACT_ASSERT(winner == 2);
            BOOST_CONTRACT_ASSERT(highlightMoves == true);
            BOOST_CONTRACT_ASSERT(size == window->getSize().y / 12);
        })
    ;

    font.loadFromFile("data/Fonts/arial.ttf");
    
    score.setFont(font);
    score.setString("Score: W-0 : B-0");
    score.setCharacterSize(0.04 * window->getSize().y);
    score.setOrigin(score.getLocalBounds().width / 2, 0);
    score.setFillColor(sf::Color::Green);
    score.setPosition(4 * window->getSize().x / 5, 0);

    size = (2 * window->getSize().y / 3) / 8;

    textRestart.setFont(font);
    textRestart.setString("RESTART");
    textRestart.setCharacterSize(0.04 * window->getSize().y);
    textRestart.setStyle(sf::Text::Bold);
    textRestart.setFillColor(sf::Color::Black);
    
    infoRestart.setFillColor(sf::Color::White);
    infoRestart.setOutlineThickness(-10.f);
    infoRestart.setOutlineColor(sf::Color::Black);
    infoRestart.setPosition(sf::Vector2f(3 * window->getSize().x / 4, window->getSize().y / 4));
    infoRestart.setSize(sf::Vector2f(textRestart.getLocalBounds().width + 40.f, textRestart.getLocalBounds().height + 40.f));

    textRestart.setPosition(infoRestart.getPosition().x + 15.f, infoRestart.getPosition().y + 10.f);

    textTurn.setFont(font);
    textTurn.setCharacterSize(0.04 * window->getSize().y);
    textTurn.setStyle(sf::Text::Bold);
    textTurn.setFillColor(sf::Color::White);
    textTurn.setPosition(3 * window->getSize().x / 4, window->getSize().y / 4 + 100.f);

    textSituation.setFont(font);
    textSituation.setCharacterSize(0.04 * window->getSize().y);
    textSituation.setStyle(sf::Text::Bold);
    textSituation.setFillColor(sf::Color::White);
    textSituation.setPosition(3 * window->getSize().x / 4, window->getSize().y / 4 + 140.f);
    textSituation.setFillColor(sf::Color::Red);

    textLastMove.setFont(font);
    textLastMove.setCharacterSize(0.04 * window->getSize().y);
    textLastMove.setStyle(sf::Text::Bold);
    textLastMove.setFillColor(sf::Color::White);
    textLastMove.setPosition(3 * window->getSize().x / 4, window->getSize().y / 4 + 230.f);

    restart();
}



void ChessGame::restart()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(selected == false);
            BOOST_CONTRACT_ASSERT(playerTurn == true);
            BOOST_CONTRACT_ASSERT(playerTurnCheck == false);
            BOOST_CONTRACT_ASSERT(mate == false);
            BOOST_CONTRACT_ASSERT(getWinner() == 2);
            BOOST_CONTRACT_ASSERT(whitePieces.size() == 16);
            BOOST_CONTRACT_ASSERT(blackPieces.size() == 16);
            BOOST_CONTRACT_ASSERT(pieceDeadIndex.empty() == true);
            BOOST_CONTRACT_ASSERT(getWhiteScore() == 0);
            BOOST_CONTRACT_ASSERT(getBlackScore() == 0);
        })
    ;

    selected = false;
    playerTurn = true;
    playerTurnCheck = false;
    mate = false;
    turn = 1;
    winner = 2;
    whitePieces.clear();
    blackPieces.clear();
    
    pieceDeadIndex.clear();
    WhiteScore = BlackScore = 0;
    SetScore();

    Piece* temp;
    temp = new Rook(false,7);
    blackPieces.push_back(temp);
    temp = new Knight(false,6);
    blackPieces.push_back(temp);
    temp = new Bishop(false,5);
    blackPieces.push_back(temp);
    temp = new King(false,4);
    blackPieces.push_back(temp);
    temp = new Queen(false,3);
    blackPieces.push_back(temp);
    temp = new Bishop(false,2);
    blackPieces.push_back(temp);
    temp = new Knight(false,1);
    blackPieces.push_back(temp);
    temp = new Rook(false,0);
    blackPieces.push_back(temp);

    temp = new Rook(true,56);
    whitePieces.push_back(temp);
    temp = new Knight(true,57);
    whitePieces.push_back(temp);
    temp = new Bishop(true,58);
    whitePieces.push_back(temp);
    temp = new Queen(true,59);
    whitePieces.push_back(temp);
    temp = new King(true,60);
    whitePieces.push_back(temp);
    temp = new Bishop(true,61);
    whitePieces.push_back(temp);
    temp = new Knight(true,62);
    whitePieces.push_back(temp);
    temp = new Rook(true,63);
    whitePieces.push_back(temp);

    
    for(int i=8;i<16;i++){
       temp = new Pawn(true,48+(i-8));
        whitePieces.push_back(temp);
        temp = new Pawn(false,15-(i-8));
        blackPieces.push_back(temp);
    
    }

    for(unsigned i = 0; i < 16; i++)
    {
        whitePieces.at(i)->setWindow(window);
        blackPieces.at(i)->setWindow(window);
    }

    calcPossibleMoves();

    textLastMove.setString(" ");
}

sf::RectangleShape ChessGame::getRestart()
{
    return infoRestart;
}

void ChessGame::updateInfo()
{
    boost::contract::check c = boost::contract::function()
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(textTurn.getString().isEmpty() == false);
            BOOST_CONTRACT_ASSERT(textSituation.getString().isEmpty() == false);
        })
    ;

    textTurn.setString("Turn: " + std::to_string(turn));
    textLastMove.setString(lastMove);

    if(!mate)
    {
        if(playerTurn)
            textSituation.setString("White's Turn");
        else
            textSituation.setString("Black's Turn");
        
        if(playerTurnCheck)
            textSituation.setString(textSituation.getString() + "\nCheck");
    }
    else
    {
        if(playerTurnCheck)
        {
            if(playerTurn)
            {
                textSituation.setString("CHECKMATE\nBlack Wins");
                winner = -1;
            }
            else
            {
                textSituation.setString("CHECKMATE\nWhite Wins");
                winner = 1;
            }
        }
        else
        {
            textSituation.setString("STALEMATE\nIts a DRAW");
            winner = 0;
        }

    }
}

void ChessGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform.combine(getTransform());

    target.draw(board);
    target.draw(infoRestart);
    target.draw(textRestart);
    target.draw(textTurn);
    target.draw(textSituation);
    target.draw(textLastMove);
    target.draw(score);

    if((selectedPiece != NULL) && (selected))
    {
        for(size_t i=0; i<possibleMovesSquares.size();i++)
        {
            target.draw(possibleMovesSquares.at(i));
        }
    }

    for(int i=0;i<16;i++)
    {
        target.draw(*whitePieces.at(i));
        target.draw(*blackPieces.at(i));
    }
}

void ChessGame::createMovesSquares()
{
    if(selectedPiece == NULL)
        return;

    possibleMovesSquares.clear();

    if(highlightMoves)
    {
        for(size_t i=0; i<selectedPiece->getPossibleMoves().size();i++)
        {
            sf::RectangleShape tmp;
            tmp.setPosition(sf::Vector2f((selectedPiece->getPossibleMoves().at(i) % 8 - 4) * size + window->getSize().x / 2, (selectedPiece->getPossibleMoves().at(i) / 8 - 4) * size + window->getSize().y / 2));
            tmp.setSize(sf::Vector2f(size, size));
            tmp.setFillColor(sf::Color(0x66b4cc50));
            possibleMovesSquares.push_back(tmp);
        }
    }

    sf::RectangleShape tmp;
    tmp.setPosition(sf::Vector2f((selectedPiece->getPosition() % 8 - 4) * size + window->getSize().x/2 , (selectedPiece->getPosition() / 8 - 4) * size + window->getSize().y / 2));
    tmp.setSize(sf::Vector2f(size, size));
    tmp.setFillColor(sf::Color(0x00000000));
    tmp.setOutlineColor(sf::Color::Red);
    tmp.setOutlineThickness(-5.f);
    possibleMovesSquares.push_back(tmp);

    return;

}

bool ChessGame::selectPiece(int pos)
{
    for(int i=0; i<16; i++)
    {
        if(playerTurn)
        { // If white turn
            if(whitePieces.at(i)->getPosition() == pos){
                selectedPiece = whitePieces.at(i);
                selected = true;
                break;
            }
        }
        else
        { // If black turn
            if(blackPieces.at(i)->getPosition() == pos){
                selectedPiece = blackPieces.at(i);
                selected = true;
                break;
            }
        }
        selected = false;
    }

    if(!selected){
        selectedPiece = NULL;
        possibleMovesSquares.clear();
        return selected;
    }


    createMovesSquares();

    return selected;
}



void ChessGame::moveSelected(int pos)
{
    bool validMove{false};

    if((selectedPiece == NULL) || !selected )
        return;
    
    // Check pos with the Piece's possibleMoves
    for(size_t i=0;i<selectedPiece->getPossibleMoves().size();i++){
        if(pos == selectedPiece->getPossibleMoves().at(i))
        {
            validMove = true;
            break;
        }
    }

    if(validMove){
        
        if((selectedPiece->getType() == 'K') && (!selectedPiece->getMoved())){
            if(selectedPiece->getPlayer()){
                if(pos == 62)
                    whitePieces.at(7)->setPosition(61);
                else if(pos == 58)
                    whitePieces.at(0)->setPosition(59);
            }
            else
            {
                if(pos == 6)
                    blackPieces.at(0)->setPosition(5);
                else if(pos == 2)
                    blackPieces.at(7)->setPosition(3);
            }
        }

        if((selectedPiece->getType() == 'P')){
            if(!selectedPiece->getMoved()){
                if(pos == (selectedPiece->getPosition() - 16)){
                    selectedPiece->setEnPassant(selectedPiece->getPosition() - 8);
                }
                else if(pos == (selectedPiece->getPosition() + 16)){
                    selectedPiece->setEnPassant(selectedPiece->getPosition() + 8);
                }
            }
            else{
                for(int i=0; i<16; i++){
                    if(playerTurn){
                        if(pos == blackPieces.at(i)->getEnPassant())
                            blackPieces.at(i)->setPosition(pos);
                    }
                    else{
                        if(pos == whitePieces.at(i)->getEnPassant())
                            whitePieces.at(i)->setPosition(pos);
                    }
                }
            }
        }
        if(selectedPiece->getMoved())
        {
            for(int i=0; i<16; i++)
            {
                whitePieces.at(i)->setEnPassant(-1);
                blackPieces.at(i)->setEnPassant(-1);
            }
        }


        selectedPiece->setPosition(pos);
              


        lastMove = "Last Turn:\n" + selectedPiece->toString();
        for(int i=0; i<16; i++){
            if(selectedPiece->getPlayer()){ // If White
                if(blackPieces.at(i)->getPosition() == pos){
                    blackPieces.at(i)->setPosition(-1);
                    break;
                }
            }
            else{ // If Black
                if(whitePieces.at(i)->getPosition() == pos){
                    whitePieces.at(i)->setPosition(-1);
                    break;
                }
            }
        }

        

        if(playerTurnCheck){
            playerTurnCheck = false;
        }

        playerTurn = !playerTurn; // Here player turn changes
        calcPossibleMoves();
    }
    
    selectedPiece = NULL;
    selected = false;
    PointsCalculator();
    PromotePawn();
    checkMate();
    updateInfo();
}

void ChessGame::calcPossibleMoves(){

    Piece* tmpPiece;

    // LOOP for every piece
    for(int x=0; x<32; x++){
        
        if(x<16)
            tmpPiece = whitePieces.at(x);
        else
            tmpPiece = blackPieces.at(x-16);
        tmpPiece->getPossibleMoves().clear();
        tmpPiece->getDangerMoves().clear();

        if(tmpPiece->getPosition() == -1)
            continue;

        // Calculate Moves for tmpPiece by piece type
        tmpPiece->calcMoves(whitePieces, blackPieces,playerTurn);
    }

    // Erase illegal moves on current player's pieces
    for(int x = 0; x < 16; x++){
        if(playerTurn){
            eraseMoves(whitePieces.at(x));
        }
        else{
            eraseMoves(blackPieces.at(x));
        }
    }

    checkMate();

    updateInfo();
    turn++;
}




void ChessGame::eraseMoves(Piece* tmpPiece){

    if(tmpPiece->getPosition() == -1)
        return;

    if(tmpPiece->getPlayer() == playerTurn){
        
        // Erase moves on same team pieces
        
        for(int i = 0; i < 16; i++){
            for(size_t j = 0; j < tmpPiece->getPossibleMoves().size(); j++){

                if(tmpPiece->getPlayer()){ // White
                    if(tmpPiece->getPossibleMoves().at(j) == whitePieces.at(i)->getPosition()){
                        tmpPiece->getPossibleMoves().erase( tmpPiece->getPossibleMoves().begin() + j );
                        break;
                    }
                }
                else{ // Black
                    if(tmpPiece->getPossibleMoves().at(j) == blackPieces.at(i)->getPosition()){
                        tmpPiece->getPossibleMoves().erase( tmpPiece->getPossibleMoves().begin() + j );
                        break;
                    } 
                }
            }
        }

        // Erase King moves on attacked squares
        if(tmpPiece->getType() == 'K'){
            for(size_t j=0; j < tmpPiece->getPossibleMoves().size(); j++){
                for(int i=0; i < 16; i++){
                    size_t o{0};
                    if(tmpPiece->getPlayer()){ // White
                        for(o=0; o < blackPieces.at(i)->getPossibleMoves().size();o++){
                            if(tmpPiece->getPossibleMoves().at(j) == blackPieces.at(i)->getPossibleMoves().at(o)){
                                tmpPiece->getPossibleMoves().erase( tmpPiece->getPossibleMoves().begin() + j-- );
                                break;
                            }
                        }
                        if( (o != blackPieces.at(i)->getPossibleMoves().size()))
                            break;;
                    }
                    else{ // Black
                        for(o=0; o < whitePieces.at(i)->getPossibleMoves().size();o++){
                            if(tmpPiece->getPossibleMoves().at(j) == whitePieces.at(i)->getPossibleMoves().at(o)){
                                tmpPiece->getPossibleMoves().erase( tmpPiece->getPossibleMoves().begin() + j-- );
                                break;
                            }
                        }
                        if( (o != whitePieces.at(i)->getPossibleMoves().size()))
                            break;;
                    }
                }
            }
        }


        // Erase moves that put current piece's king in check        
        if(tmpPiece->getType() != 'K'){
            for(int i=0; i<16; i++){
                if     ( playerTurn && (blackPieces.at(i)->getDangerMoves().size() > 1) ){
                    for(size_t j=0; j<blackPieces.at(i)->getDangerMoves().size(); j++){
                        if(blackPieces.at(i)->getDangerMoves().at(j) == tmpPiece->getPosition()){
                            std::vector<int> tmpMoves;
                            for(size_t x=0; x<tmpPiece->getPossibleMoves().size(); x++){
                                for(size_t k=0; k<blackPieces.at(i)->getDangerMoves().size(); k++){
                                    if(tmpPiece->getPossibleMoves().at(x) == blackPieces.at(i)->getDangerMoves().at(k))
                                        tmpMoves.push_back( tmpPiece->getPossibleMoves().at(x) );
                                }
                            }
                            tmpPiece->getPossibleMoves().clear();
                            tmpPiece->getPossibleMoves() = tmpMoves;
                            break;
                        }
                    }
                }
                else if(!playerTurn && (whitePieces.at(i)->getDangerMoves().size() > 1) ){
                    for(size_t j=0; j<whitePieces.at(i)->getDangerMoves().size(); j++){
                        if(whitePieces.at(i)->getDangerMoves().at(j) == tmpPiece->getPosition()){
                            std::vector<int> tmpMoves;
                            for(size_t x=0; x<tmpPiece->getPossibleMoves().size(); x++){
                                for(size_t k=0; k<whitePieces.at(i)->getDangerMoves().size(); k++){
                                    if(tmpPiece->getPossibleMoves().at(x) == whitePieces.at(i)->getDangerMoves().at(k))
                                        tmpMoves.push_back( tmpPiece->getPossibleMoves().at(x) );
                                }
                            }
                            tmpPiece->getPossibleMoves().clear();
                            tmpPiece->getPossibleMoves() = tmpMoves;
                            break;
                        }
                    }
                }
            }
        }


    }
}

void ChessGame::calcCastling(Piece* tmpPiece){

    if( playerTurnCheck || (tmpPiece->getType() != 'K') || tmpPiece->getMoved() || (tmpPiece->getPlayer() != playerTurn))
        return;

    
    if(tmpPiece->getPlayer()){ // If White King
        // whitePieces[0] Bot Left Rook, whitePieces[7] Bot Right Rook
        if(!whitePieces.at(7)->getMoved()){
            int i{0};
            for(i=0;i<16;i++){
                if((whitePieces.at(i)->getPosition() == 61) || (whitePieces.at(i)->getPosition() == 62)){
                    i=17;
                    break;
                }
                if((blackPieces.at(i)->getPosition() == 61) || (blackPieces.at(i)->getPosition() == 62)){
                    i = 17;
                    break;
                }
            }
            if(i == 16){
                for(i=0; i<16; i++){
                    for(size_t j=0; j<blackPieces.at(i)->getPossibleMoves().size(); j++){
                        if((blackPieces.at(i)->getPossibleMoves().at(j) == 61) || (blackPieces.at(i)->getPossibleMoves().at(j) == 62) || (blackPieces.at(i)->getPossibleMoves().at(j) == 60)){
                            i = 17;
                            break;
                        }
                    }
                    if(i == 17) break;
                }
            }
            if(i != 17){
                
                tmpPiece->getPossibleMoves().push_back(62);
            }
        }

        if(!whitePieces.at(0)->getMoved()){
            int i{0};
            for(i=0;i<16;i++){
                if((whitePieces.at(i)->getPosition() == 57) || (whitePieces.at(i)->getPosition() == 58) || (whitePieces.at(i)->getPosition() == 59)){
                    i=17;
                    break;
                }
                if((blackPieces.at(i)->getPosition() == 57) || (blackPieces.at(i)->getPosition() == 58) || (blackPieces.at(i)->getPosition() == 59)){
                    i =17;
                    break;
                }
            }
            if(i == 16){
                for(i=0; i<16; i++){
                    for(size_t j=0; j<blackPieces.at(i)->getPossibleMoves().size(); j++){
                        if((blackPieces.at(i)->getPossibleMoves().at(j) == 58) || (blackPieces.at(i)->getPossibleMoves().at(j) == 59) || (blackPieces.at(i)->getPossibleMoves().at(j) == 60)){
                            i = 17;
                            break;
                        }
                    }
                    if(i == 17) break;
                }
            }
            if(i != 17){
                tmpPiece->getPossibleMoves().push_back(58);
            }
        }
    }
    else{ // If Black King
        // blackPieces[7] Top Left Rook, blackPieces[0] Top Right Rook
        if(!blackPieces.at(7)->getMoved()){
            int i{0};
            for(i=0;i<16;i++){
                if((whitePieces.at(i)->getPosition() == 3) || (whitePieces.at(i)->getPosition() == 2) || (whitePieces.at(i)->getPosition() == 1)){
                    i=17;
                    break;
                }
                if((blackPieces.at(i)->getPosition() == 3) || (blackPieces.at(i)->getPosition() == 2) || (blackPieces.at(i)->getPosition() == 1)){
                    i=17;
                    break;
                }
            }
            if(i == 16){
                for(i=0; i<16; i++){
                    for(size_t j=0; j<whitePieces.at(i)->getPossibleMoves().size(); j++){
                        if((whitePieces.at(i)->getPossibleMoves().at(j) == 3) || (whitePieces.at(i)->getPossibleMoves().at(j) == 2) || (whitePieces.at(i)->getPossibleMoves().at(j) == 4)){
                            i = 17;
                            break;
                        }
                    }
                    if(i == 17) break;
                }
            }
            if(i != 17){
                tmpPiece->getPossibleMoves().push_back(2);
            }
        }

        if(!blackPieces.at(0)->getMoved()){
            int i{0};
            for(i=0;i<16;i++){
                if((whitePieces.at(i)->getPosition() == 5) || (whitePieces.at(i)->getPosition() == 6)){
                    i=17;
                    break;
                }
                if((blackPieces.at(i)->getPosition() == 5) || (blackPieces.at(i)->getPosition() == 6)){
                    i=17;
                    break;
                }
            }
            if(i == 16){
                for(i=0; i<16; i++){
                    for(size_t j=0; j<whitePieces.at(i)->getPossibleMoves().size(); j++){
                        if((whitePieces.at(i)->getPossibleMoves().at(j) == 5) || (whitePieces.at(i)->getPossibleMoves().at(j) == 6) || (whitePieces.at(i)->getPossibleMoves().at(j) == 4)){
                            i = 17;
                            break;
                        }
                    }
                    if(i == 17) break;
                }
            }
            if(i != 17){
                tmpPiece->getPossibleMoves().push_back(6);
            }
        }
    }
}




void ChessGame::checkMate(){
    // No more than two piece can check a King.
    // A single check can be unchecked either by the King moving to
        // a square that is not attacked, or if another piece blocks/kills the attacking piece
    // A double check can be unchecked only by moving the checked King

    Piece* check1{NULL};
    Piece* check2{NULL};

    // Check if current player's King is in check
    // whitePieces[4] is white King , blackPieces[3] is black King
    for(int i = 0; i<16; i++)
    {
        if(playerTurn)
        { // White turn
            for(size_t j=0; j < blackPieces.at(i)->getPossibleMoves().size(); j++)
            {
                if(whitePieces.at(4)->getPosition() == blackPieces.at(i)->getPossibleMoves().at(j))
                {
                    if(check1 == NULL)
                    {
                        playerTurnCheck = true;
                        check1 = blackPieces.at(i);
                        break;
                    }
                    else if(check2 == NULL)
                    {
                        //playerTurnCheck = true;
                        check2 = blackPieces.at(i);
                        break;
                    }
                }
            }
        }
        else{ // Black turn
            for(size_t j=0; j < whitePieces.at(i)->getPossibleMoves().size(); j++){
                if(blackPieces.at(3)->getPosition() == whitePieces.at(i)->getPossibleMoves().at(j)){
                    if(check1 == NULL){
                        playerTurnCheck = true;
                        check1 = whitePieces.at(i);
                        break;
                    }
                    else if(check2 == NULL){
                        //playerTurnCheck = true;
                        check2 = whitePieces.at(i);
                        break;
                    }
                }
            }
        }

        if(check2 != NULL)
            break;
    }

    // Check which current player pieces moves put its King out of check
    // If no moves then Check Mate, current player loses
    if(playerTurnCheck){
        if(check2 != NULL){ // If double check, clear current player's pieces moves except king's
            if(playerTurn)
            {
                for(int i=0; i<16; i++)
                    if(whitePieces.at(i)->getType() != 'K')
                        whitePieces.at(i)->getPossibleMoves().clear();
            }
            else
            {
                for(int i=0; i<16; i++)
                    if(blackPieces.at(i)->getType() != 'K')
                        blackPieces.at(i)->getPossibleMoves().clear();
            }
        }
        else{ // If single check

            for(int j=0; j<16; j++){ // pieces array counter
                std::vector<int> tmpMoves;

                if(playerTurn){ // If White turn
                    if(whitePieces.at(j)->getType() == 'K')
                        continue;
                    for(size_t o = 0; o < whitePieces.at(j)->getPossibleMoves().size(); o++){
                        if(whitePieces.at(j)->getPossibleMoves().empty())
                            break;
                        for(size_t i=0; i < check1->getDangerMoves().size(); i++){ // Checking piece moves counter
                            if((whitePieces.at(j)->getPossibleMoves().at(o) == check1->getDangerMoves().at(i)) ){
                                tmpMoves.push_back( whitePieces.at(j)->getPossibleMoves().at(o) );
                                break;
                            }
                        }
                    }

                    whitePieces.at(j)->getPossibleMoves().clear();
                    whitePieces.at(j)->getPossibleMoves() = tmpMoves;
                }
                else{ // If Black turn
                    if(blackPieces.at(j)->getType() == 'K')
                        continue;
                    for(size_t o = 0; o < blackPieces.at(j)->getPossibleMoves().size(); o++){
                        if(blackPieces.at(j)->getPossibleMoves().empty())
                            break;
                        for(size_t i=0; i < check1->getDangerMoves().size(); i++){ // Checking piece moves counter
                            if((blackPieces.at(j)->getPossibleMoves().at(o) == check1->getDangerMoves().at(i)) ){
                                tmpMoves.push_back( blackPieces.at(j)->getPossibleMoves().at(o) );
                                break;
                            }
                        }
                    }
                    blackPieces.at(j)->getPossibleMoves().clear();
                    blackPieces.at(j)->getPossibleMoves() = tmpMoves;
                }
            }
        }


        //Bug fix
        // whitePieces[4] is white King , blackPieces[3] is black King
        Piece* curKing;
        if(playerTurn){
            curKing = whitePieces.at(4);
        }
        else{
            curKing = blackPieces.at(3);
        }
        if(check1 != NULL){
            if((check1->getType() == 'Q') || (check1->getType() == 'R' || (check1->getType() == 'B'))){
                int checkPos{check1->getPosition()};

                if((check1->getType() == 'Q') || (check1->getType() == 'R')){
                    for(size_t i=0; i< curKing->getPossibleMoves().size(); i++){
                        if(curKing->getPossibleMoves().at(i) != checkPos){
                            if     ((curKing->getPossibleMoves().at(i) % 8) == (checkPos % 8))
                                curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            else if((curKing->getPossibleMoves().at(i) / 8) == (checkPos / 8))
                                curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                        }
                    }
                }

                for(size_t i=0; i< curKing->getPossibleMoves().size(); i++){
                    if(curKing->getPossibleMoves().at(i) != checkPos){
                        if((curKing->getPosition()%8) < (checkPos%8)){ // King left of Check
                            if((curKing->getPosition()/8) < (checkPos/8)){ // King top of Check
                                if( ((curKing->getPossibleMoves().at(i)%8) < (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) <  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                            else if((checkPos/8) < (curKing->getPosition()/8)){ // King under Check
                                if( ((curKing->getPossibleMoves().at(i)%8) < (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) >  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                        else if((checkPos%8) < (curKing->getPosition()%8) ){ // King right of Check
                            if((curKing->getPosition()/8) < (checkPos/8)){ // King top of Check
                                if( ((curKing->getPossibleMoves().at(i)%8) > (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) <  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                            else if((checkPos/8) < (curKing->getPosition()/8)){ // King under Check
                                if( ((curKing->getPossibleMoves().at(i)%8) > (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) >  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                    }
                }
            }
        }
        //Bug fix
        if(check2 != NULL){
            if((check2->getType() == 'Q') || (check2->getType() == 'R' || (check2->getType() == 'B'))){
                int checkPos{check2->getPosition()};

                if((check2->getType() == 'Q') || (check2->getType() == 'R')){
                    for(size_t i=0; i< curKing->getPossibleMoves().size(); i++){
                        if(curKing->getPossibleMoves().at(i) != checkPos){
                            if     ((curKing->getPossibleMoves().at(i) % 8) == (checkPos % 8))
                                curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            else if((curKing->getPossibleMoves().at(i) / 8) == (checkPos / 8))
                                curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                        }
                    }
                }

                for(size_t i=0; i< curKing->getPossibleMoves().size(); i++){
                    if(curKing->getPossibleMoves().at(i) != checkPos){
                        if((curKing->getPosition()%8) < (checkPos%8)){ // King left of Check
                            if((curKing->getPosition()/8) < (checkPos/8)){ // King top of Check
                                if( ((curKing->getPossibleMoves().at(i)%8) < (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) <  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                            else if((checkPos/8) < (curKing->getPosition()/8)){ // King under Check
                                if( ((curKing->getPossibleMoves().at(i)%8) < (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) >  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                        else if((checkPos%8) < (curKing->getPosition()%8) ){ // King right of Check
                            if((curKing->getPosition()/8) < (checkPos/8)){ // King top of Check
                                if( ((curKing->getPossibleMoves().at(i)%8) > (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) <  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                            else if((checkPos/8) < (curKing->getPosition()/8)){ // King under Check
                                if( ((curKing->getPossibleMoves().at(i)%8) > (curKing->getPosition()%8)) && ((curKing->getPossibleMoves().at(i)/8) >  (curKing->getPosition()/8))  )
                                    curKing->getPossibleMoves().erase( curKing->getPossibleMoves().begin() + i--);
                            }
                        }
                    }
                }
            }
        }

    }
    else{
        calcCastling(whitePieces.at(4));
        calcCastling(blackPieces.at(3));
    }

    // Check if current player has any available moves
    int i{0};
    for(i=0; i<16; i++){
        if(playerTurn){
            if(!whitePieces.at(i)->getPossibleMoves().empty())
                break;
        }
        else{
            if(!blackPieces.at(i)->getPossibleMoves().empty())
                break;
        }
    }
    if(i==16){ 
        mate = true;
    }

}

void ChessGame::SetScore()
{
    std::ostringstream text;
    text << "Score: W-"<< WhiteScore << " : B-" << BlackScore;
    score.setString(text.str());
}

bool ChessGame::pointsCheck(int i, bool r)
{
    std::pair<int,bool> p = {i,r};
    for (auto &j: pieceDeadIndex)
    {
        if(p == j)
        {
            return true;
        }
    }
    return false;
}

void ChessGame::PointsCalculator()
{
    for(int i=0; i<16; i++)
    {
        switch (whitePieces.at(i)->getType())
        {
            case 'P':if(whitePieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,true))
                            break;
                        BlackScore += 1;
                        pieceDeadIndex.push_back({i,true});
                     }  
                     break;
            case 'Q':if(whitePieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,true))
                            break;
                        BlackScore += 9;
                        pieceDeadIndex.push_back({i,true});
                     }  
                     break;
            case 'B':if(whitePieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,true))
                            break;
                        BlackScore += 3;
                        pieceDeadIndex.push_back({i,true});
                     }  
                     break;
            case 'N':if(whitePieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,true))
                            break;
                        BlackScore += 3;
                        pieceDeadIndex.push_back({i,true});
                     }  
                     break;
            case 'R':if(whitePieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,true))
                            break;
                        BlackScore += 5;
                        pieceDeadIndex.push_back({i,true});
                     }  
                     break;
            default:  break;
        }
        SetScore();
    }
    for(int i=0; i<16; i++)
    {
        switch (blackPieces.at(i)->getType())
        {
            case 'P':if(blackPieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,false))
                            break;
                        WhiteScore += 1;
                        pieceDeadIndex.push_back({i,false});
                     }  
                     break;
            case 'Q':if(blackPieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,false))
                            break;
                        WhiteScore += 9;
                        pieceDeadIndex.push_back({i,false});
                     }  
                     break;
            case 'B':if(blackPieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,false))
                            break;
                        WhiteScore += 3;
                        pieceDeadIndex.push_back({i,false});
                     }  
                     break;
            case 'N':if(blackPieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,false))
                            break;
                        WhiteScore += 3;
                        pieceDeadIndex.push_back({i,false});
                     }  
                     break;
            case 'R':if(blackPieces.at(i)->getPosition() == -1)
                     {
                        if(pointsCheck(i,false))
                            break;
                        WhiteScore += 5;
                        pieceDeadIndex.push_back({i,false});
                     }  
                     break;
            default: break;
        }
        SetScore();
    }
}

int ChessGame::getWinner()
{
    return winner;
}

int ChessGame::getBlackScore()
{
    return BlackScore;
}
int ChessGame::getWhiteScore()
{
    return WhiteScore;
}

void ChessGame::toggleHighlightMoves(bool value)
{
    highlightMoves = value;
}

void ChessGame::PromotePawn()
{
    for(unsigned i = 8; i < 16; i++)
    {
        if((whitePieces.at(i)->getPosition() / 8) == 0)
        {
            if(whitePieces.at(i)->getType() == 'P')
            {
                Piece* temp = new Queen(whitePieces.at(i)->getPlayer(), whitePieces.at(i)->getPosition(), true);
                whitePieces.at(i) = temp;
                whitePieces.at(i)->setWindow(window);
                whitePieces.at(i)->calcMoves(whitePieces, blackPieces,playerTurn);
            }
        }
        if(blackPieces.at(i)->getPosition() / 8 == 7)
        {
            if(blackPieces.at(i)->getType() == 'P')
            {
                Piece* temp = new Queen(blackPieces.at(i)->getPlayer(), blackPieces.at(i)->getPosition(), true);
                blackPieces.at(i) = temp;
                blackPieces.at(i)->setWindow(window);
                blackPieces.at(i)->calcMoves(whitePieces, blackPieces,playerTurn);
            }
        }
    }
}

std::vector<Piece*>& ChessGame::getWhitePieces()
{
    return whitePieces;
}

std::vector<Piece*>& ChessGame::getBlackPieces()
{
    return blackPieces;
}

bool ChessGame::getPlayerTurn()
{
    return playerTurn;
}