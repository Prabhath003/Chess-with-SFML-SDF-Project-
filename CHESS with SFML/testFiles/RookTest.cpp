#include <gtest/gtest.h>

#include "Rook.hpp"

TEST(RookTest, moveVariableInitially)
{
    Rook piece(true, 16);

    ASSERT_EQ(piece.getMoved(), false);
}