#pragma once

// including the files
#include "Piece.hpp"

// King class
class King
#define BASES public Piece
    : BASES
{
    public:
typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
#undef BASES
        // contructor taking the position of piece and its color
        King(bool player, int pos);
        // overrided function to calculate the Possible moves
        void calcMoves(std::vector<Piece*> whitePieces, std::vector<Piece*> blackPieces,
            bool playerturn, boost::contract::virtual_ *v = 0) override;
        BOOST_CONTRACT_OVERRIDE(calcMoves);
};