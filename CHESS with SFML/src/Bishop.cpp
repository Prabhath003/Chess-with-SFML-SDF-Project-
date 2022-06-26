#include "Bishop.hpp"

Bishop::Bishop(bool player, int pos) : Piece()
{
    boost::contract::old_ptr<bool> old_player = BOOST_CONTRACT_OLDOF(player);
    boost::contract::old_ptr<int> old_pos = BOOST_CONTRACT_OLDOF(pos);
    boost::contract::check c = boost::contract::constructor(this)
        .postcondition([&] { // postconditon checks
            BOOST_CONTRACT_ASSERT(player == *old_player);
            BOOST_CONTRACT_ASSERT(pos == *old_pos);
            BOOST_CONTRACT_ASSERT(m_position == pos);
            BOOST_CONTRACT_ASSERT(m_player == player);
            BOOST_CONTRACT_ASSERT(m_type == 'B');
        })
    ;

    m_position = pos;
    m_player = player;
    m_type = 'B';
}

void Bishop::calcMoves(std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces, bool playerTurn,
    boost::contract::virtual_ *v)
{
    boost::contract::old_ptr<size_t> old_whitesize = BOOST_CONTRACT_OLDOF(whitePieces.size());
    boost::contract::old_ptr<size_t> old_blacksize = BOOST_CONTRACT_OLDOF(blackPieces.size());
    boost::contract::old_ptr<bool> old_playerTurn = BOOST_CONTRACT_OLDOF(playerTurn);
    boost::contract::check c = boost::contract::public_function<
        override_calcMoves>(v, &Bishop::calcMoves, this, whitePieces, blackPieces, playerTurn)
        .postcondition([&] {
            BOOST_CONTRACT_ASSERT(whitePieces.size() == *old_whitesize);
            BOOST_CONTRACT_ASSERT(blackPieces.size() == *old_blacksize);
            BOOST_CONTRACT_ASSERT(playerTurn == *old_playerTurn);
        })
    ;
    
    //Normal Bishop Moving
    int piecePos{this->getPosition()};
    int posCounter{9};

    bool dangerMove{false};
    bool finishLoop{false};

    this->getPossibleMoves().clear();
    this->getDangerMoves().clear();

    // Bishop moves towards top left
    while( ((piecePos-posCounter) >= 0) && (((piecePos-posCounter) % 8) < (piecePos % 8)) ){
        if(!finishLoop){
            for(int i = 0; i<16; i++){
                if( (whitePieces[i]->getPosition() == (piecePos-posCounter)) || (blackPieces[i]->getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            this->getPossibleMoves().push_back(piecePos-posCounter);
        }

        if(!dangerMove){
            // whitePieces[4] is white King , blackPieces[3] is black King
            this->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) == blackPieces[3]->getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == whitePieces[4]->getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }

    // Bishop moves towards bottom right
    if(!dangerMove) this->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 9;
    while( ((piecePos+posCounter) <= 63) && (((piecePos+posCounter) % 8) > (piecePos % 8)) ){
        if(!finishLoop){
            for(int i = 0; i<16; i++){
                if( (whitePieces[i]->getPosition() == (piecePos+posCounter)) || (blackPieces[i]->getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            this->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            // whitePieces[4] is white King , blackPieces[3] is black King
            this->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) == blackPieces[3]->getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == whitePieces[4]->getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 9;
    }

    // Bishop moves towards top right
    if(!dangerMove) this->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while( ((piecePos-posCounter) >= 0) && (((piecePos-posCounter) % 8) > (piecePos % 8)) ){
        if(!finishLoop){
            for(int i = 0; i<16; i++){
                if( (whitePieces[i]->getPosition() == (piecePos-posCounter)) || (blackPieces[i]->getPosition() == (piecePos-posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            this->getPossibleMoves().push_back(piecePos-posCounter);
        }

        if(!dangerMove){
            // whitePieces[4] is white King , blackPieces[3] is black King
            this->getDangerMoves().push_back(piecePos-posCounter);
            if(!playerTurn){
                if( (piecePos-posCounter) == blackPieces[3]->getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos-posCounter) == whitePieces[4]->getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    // Bishop moves towards bottom left
    if(!dangerMove) this->getDangerMoves().clear();
    finishLoop = false;
    posCounter = 7;
    while( ((piecePos+posCounter) <= 63) && (((piecePos+posCounter) % 8) < (piecePos % 8)) ){
        if(!finishLoop){
            for(int i = 0; i<16; i++){
                if( (whitePieces[i]->getPosition() == (piecePos+posCounter)) || (blackPieces[i]->getPosition() == (piecePos+posCounter)) ){
                    finishLoop = true;
                    break;
                }
            }
            this->getPossibleMoves().push_back(piecePos+posCounter);
        }

        if(!dangerMove){
            // whitePieces[4] is white King , blackPieces[3] is black King
            this->getDangerMoves().push_back(piecePos+posCounter);
            if(!playerTurn){
                if( (piecePos+posCounter) == blackPieces[3]->getPosition() )
                    dangerMove = true;
            }
            else{
                if( (piecePos+posCounter) == whitePieces[4]->getPosition() )
                    dangerMove = true;
            }
        }

        posCounter += 7;
    }

    if(!dangerMove) this->getDangerMoves().clear();
    
    
    if(!this->getDangerMoves().empty()){
        int collisions{0};
        for(size_t j=0; j<this->getDangerMoves().size(); j++){
            for(int i=0; i<16; i++){
                if(this->getDangerMoves().at(j) == blackPieces[i]->getPosition()){
                    collisions++;
                    if(!this->getPlayer())
                        collisions++;
                }
                if(this->getDangerMoves().at(j) == whitePieces[i]->getPosition()){
                    collisions++;
                    if(this->getPlayer())
                        collisions++;
                }
            }
        }

        if(collisions > 2)
            this->getDangerMoves().clear();
    }
    
    this->getDangerMoves().push_back( this->getPosition() );
    
}