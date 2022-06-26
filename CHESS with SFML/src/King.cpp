#include "King.hpp"

King::King(bool player, int pos) : Piece()
{
    boost::contract::old_ptr<bool> old_player = BOOST_CONTRACT_OLDOF(player);
    boost::contract::old_ptr<int> old_pos = BOOST_CONTRACT_OLDOF(pos);
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] { // postconditon checks
            BOOST_CONTRACT_ASSERT(player == *old_player);
            BOOST_CONTRACT_ASSERT(pos == *old_pos);
            BOOST_CONTRACT_ASSERT(m_position == pos);
            BOOST_CONTRACT_ASSERT(m_player == player);
            BOOST_CONTRACT_ASSERT(m_type == 'K');
        })
    ;

    m_position = pos;
    m_player = player;
    m_type = 'K';
}

void King::calcMoves(std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces, bool playerTurn,
    boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<size_t> old_whitesize = BOOST_CONTRACT_OLDOF(whitePieces.size());
    boost::contract::old_ptr<size_t> old_blacksize = BOOST_CONTRACT_OLDOF(blackPieces.size());
    boost::contract::old_ptr<bool> old_playerTurn = BOOST_CONTRACT_OLDOF(playerTurn);
    boost::contract::check c = boost::contract::public_function<
        override_calcMoves>(v, &King::calcMoves, this, whitePieces, blackPieces, playerTurn)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(whitePieces.size() == *old_whitesize);
            BOOST_CONTRACT_ASSERT(blackPieces.size() == *old_blacksize);
            BOOST_CONTRACT_ASSERT(playerTurn == *old_playerTurn);
        })
    ;

    int piecePos{this->getPosition()};
    this->getPossibleMoves().clear();

    if((piecePos / 8) != 0){
        this->getPossibleMoves().push_back(piecePos - 8);
        if((piecePos % 8) != 0)
            this->getPossibleMoves().push_back(piecePos - 9);
        if((piecePos % 8) != 7)
            this->getPossibleMoves().push_back(piecePos - 7);
    }
    if((piecePos / 8) != 7){
        this->getPossibleMoves().push_back(piecePos + 8);
        if((piecePos % 8) != 0)
            this->getPossibleMoves().push_back(piecePos + 7);
        if((piecePos % 8) != 7)
            this->getPossibleMoves().push_back(piecePos + 9);
    }
    if((piecePos % 8) != 0)
        this->getPossibleMoves().push_back(piecePos - 1);
    if((piecePos % 8) != 7)
        this->getPossibleMoves().push_back(piecePos + 1);


    //calcCastling(tmpPiece);
}

