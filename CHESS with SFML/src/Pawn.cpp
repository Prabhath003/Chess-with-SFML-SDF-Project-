#include "Pawn.hpp"

Pawn::Pawn(bool player, int pos) : Piece()
{
    boost::contract::old_ptr<bool> old_player = BOOST_CONTRACT_OLDOF(player);
    boost::contract::old_ptr<int> old_pos = BOOST_CONTRACT_OLDOF(pos);
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] { // postconditon checks
            BOOST_CONTRACT_ASSERT(player == *old_player);
            BOOST_CONTRACT_ASSERT(pos == *old_pos);
            BOOST_CONTRACT_ASSERT(m_position == pos);
            BOOST_CONTRACT_ASSERT(m_player == player);
            BOOST_CONTRACT_ASSERT(m_type == 'P');
        })
    ;

    m_position = pos;
    m_player = player;
    m_type = 'P';
}

void Pawn::calcMoves(std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces, bool playerTurn,
    boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<size_t> old_whitesize = BOOST_CONTRACT_OLDOF(whitePieces.size());
    boost::contract::old_ptr<size_t> old_blacksize = BOOST_CONTRACT_OLDOF(blackPieces.size());
    boost::contract::old_ptr<bool> old_playerTurn = BOOST_CONTRACT_OLDOF(playerTurn);
    boost::contract::check c = boost::contract::public_function<
        override_calcMoves>(v, &Pawn::calcMoves, this, whitePieces, blackPieces, playerTurn)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(whitePieces.size() == *old_whitesize);
            BOOST_CONTRACT_ASSERT(blackPieces.size() == *old_blacksize);
            BOOST_CONTRACT_ASSERT(playerTurn == *old_playerTurn);
        })
    ;
     
    this->getPossibleMoves().clear();

    int piecePos{this->getPosition()};
    
    if (this->getPlayer()){ // If pawn is white
        if((piecePos / 8) != 0){
            int i{0};
            for(i = 0; i<16;i++){
                if((whitePieces[i]->getPosition() == (piecePos - 8) ) || (blackPieces[i]->getPosition() == (piecePos - 8) ))
                    break;
            }
            if((i == 16) && playerTurn){
                this->getPossibleMoves().push_back(piecePos - 8);

                if(!this->getMoved()){
                    for(i = 0; i<16;i++){
                        if((whitePieces[i]->getPosition() == (piecePos - 16) ) || (blackPieces[i]->getPosition() == (piecePos - 16) ))
                            break;
                    }
                    if(i == 16)
                        this->getPossibleMoves().push_back(piecePos - 16);
                }
            }

            if((piecePos % 8) != 0){
                for(i = 0; i<16; i++){
                    if( !playerTurn || (blackPieces[i]->getPosition() == (piecePos - 9)) || (whitePieces[i]->getPosition() == (piecePos - 9)) ){
                        this->getPossibleMoves().push_back(piecePos - 9);
                        break;
                    }
                    else if((blackPieces[i]->getEnPassant() == (piecePos - 9)) && (blackPieces[i]->getEnPassant() != -1)){
                        this->getPossibleMoves().push_back(piecePos - 9);
                        break;
                    }
                }
            }

            if((piecePos % 8) != 7){
                for(i = 0; i<16; i++){
                    if( !playerTurn || (blackPieces[i]->getPosition() == (piecePos - 7)) || (whitePieces[i]->getPosition() == (piecePos - 7)) ){
                        this->getPossibleMoves().push_back(piecePos - 7);
                        break;
                    }
                    else if((blackPieces[i]->getEnPassant() == (piecePos - 7)) && (blackPieces[i]->getEnPassant() != -1)){
                        this->getPossibleMoves().push_back(piecePos - 7);
                        break;
                    }
                }                    
            }

        }
                

    }
    else{ //if pawn is black

        if((piecePos / 8) != 7){
            int i{0};
            for(i = 0; i<16;i++){
                if((whitePieces[i]->getPosition() == (piecePos + 8) ) || (blackPieces[i]->getPosition() == (piecePos + 8) ))
                    break;
            }
            if((i == 16) && !playerTurn){
                this->getPossibleMoves().push_back(piecePos + 8);

                if(!this->getMoved()){
                    for(i = 0; i<16;i++){
                        if((whitePieces[i]->getPosition() == (piecePos + 16) ) || (blackPieces[i]->getPosition() == (piecePos + 16) ))
                            break;
                    }
                    if(i == 16)
                        this->getPossibleMoves().push_back(piecePos + 16);
                }
            }

            if((piecePos % 8) != 0){
                for(i = 0; i<16; i++){
                    if( playerTurn || (whitePieces[i]->getPosition() == (piecePos + 7)) || (blackPieces[i]->getPosition() == (piecePos + 7)) ){
                        this->getPossibleMoves().push_back(piecePos + 7);
                        break;
                    }
                    else if((whitePieces[i]->getEnPassant() == (piecePos + 7)) && (whitePieces[i]->getEnPassant() != -1)){
                        this->getPossibleMoves().push_back(piecePos + 7);
                        break;
                    }
                }                    
            }

            if((piecePos % 8) != 7){
                for(i = 0; i<16; i++){
                    if( playerTurn || (whitePieces[i]->getPosition() == (piecePos + 9)) || (blackPieces[i]->getPosition() == (piecePos + 9)) ){
                        this->getPossibleMoves().push_back(piecePos + 9);
                        break;
                    }
                    else if((whitePieces[i]->getEnPassant() == (piecePos + 9)) && (whitePieces[i]->getEnPassant() != -1)){
                        this->getPossibleMoves().push_back(piecePos + 9);
                        break;
                    }
                }                    
            }

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
