#include <gtest/gtest.h>

#include "Pawn.hpp"

TEST(EN_PASSANT ,PAWN_TEST_ON_FIRST_MOVE)
{
    Pawn p1(false, 15);

    ASSERT_EQ(p1.getEnPassant(),-1);
}