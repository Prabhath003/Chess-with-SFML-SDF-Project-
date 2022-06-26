#include <gtest/gtest.h>

#include "Pawn.hpp"

TEST(PawnTest, moveVariableInitially)
{
    Pawn piece(true, 16);

    ASSERT_EQ(piece.getMoved(), false);
}