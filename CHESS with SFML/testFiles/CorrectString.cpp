#include <gtest/gtest.h>

#include "Queen.hpp"

TEST(CorrectString, AssignPieceCorrespondingString)
{
    Queen piece(true, 59);

    ASSERT_EQ(piece.toString(),"White Queen \nto position\nX: 4  Y: 8\n");
}