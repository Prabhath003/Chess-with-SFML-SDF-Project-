#include "Knight.hpp"

Knight::Knight(bool player, int pos) : Piece()
{
    boost::contract::old_ptr<bool> old_player = BOOST_CONTRACT_OLDOF(player);
    boost::contract::old_ptr<int> old_pos = BOOST_CONTRACT_OLDOF(pos);
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] { // postconditon checks
            BOOST_CONTRACT_ASSERT(player == *old_player);
            BOOST_CONTRACT_ASSERT(pos == *old_pos);
            BOOST_CONTRACT_ASSERT(m_position == pos);
            BOOST_CONTRACT_ASSERT(m_player == player);
            BOOST_CONTRACT_ASSERT(m_type == 'N');
        })
    ;

    m_position = pos;
    m_player = player;
    m_type = 'N';
}

void Knight::calcMoves(std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces, bool playerTurn,
    boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<size_t> old_whitesize = BOOST_CONTRACT_OLDOF(whitePieces.size());
    boost::contract::old_ptr<size_t> old_blacksize = BOOST_CONTRACT_OLDOF(blackPieces.size());
    boost::contract::old_ptr<bool> old_playerTurn = BOOST_CONTRACT_OLDOF(playerTurn);
    boost::contract::check c = boost::contract::public_function<
        override_calcMoves>(v, &Knight::calcMoves, this, whitePieces, blackPieces, playerTurn)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(whitePieces.size() == *old_whitesize);
            BOOST_CONTRACT_ASSERT(blackPieces.size() == *old_blacksize);
            BOOST_CONTRACT_ASSERT(playerTurn == *old_playerTurn);
        })
    ;

    this->getPossibleMoves().clear();

    int piecePos{this->getPosition()};

    if((piecePos / 8) != 0 ){
        if((piecePos % 8) >= 2 )
            this->getPossibleMoves().push_back(piecePos - 10);
        if( (piecePos % 8) <= 5 )
            this->getPossibleMoves().push_back(piecePos - 6);
        if((piecePos / 8) != 1){
            if((piecePos % 8) >= 1 )
                this->getPossibleMoves().push_back(piecePos - 17);
            if((piecePos % 8) <= 6 )
                this->getPossibleMoves().push_back(piecePos - 15);
        }
    }
    if((piecePos / 8) != 7){
        if((piecePos % 8) >= 2 )
            this->getPossibleMoves().push_back(piecePos + 6);
        if( (piecePos % 8) <= 5 )
            this->getPossibleMoves().push_back(piecePos + 10);
        if((piecePos / 8) != 6){
            if((piecePos % 8) >= 1 )
                this->getPossibleMoves().push_back(piecePos + 15);
            if((piecePos % 8) <= 6 )
                this->getPossibleMoves().push_back(piecePos + 17);
        }
    }

    this->getDangerMoves().clear();

    for(size_t i = 0; i < this->getPossibleMoves().size(); i++){

        if(!playerTurn){
            if( (this->getPossibleMoves().at(i)) == blackPieces[3]->getPosition() )
                this->getDangerMoves().push_back( this->getPossibleMoves().at(i) );
        }
        else{
            if( (this->getPossibleMoves().at(i)) == whitePieces[4]->getPosition() )
                this->getDangerMoves().push_back( this->getPossibleMoves().at(i) );
        }

    }

    this->getDangerMoves().push_back( this->getPosition() );
}
