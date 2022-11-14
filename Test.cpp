#include "gtest/gtest.h"
#include "GF2.h"


using namespace std;

TEST(sromTest512,testSum1)
{
    GF2 A("f01327c24a59ce5b5fef9dcb98afb2f9c18bbaadd8fa");
    GF2 B("881b59763c21011d3c0359924251f014c4d8e9b3dcfc");

    A += B;
    string actual = A.convert64bitToHex();
    string expected = "78087eb47678cf4663ecc459dafe42ed0553531e0406";

    EXPECT_EQ(actual,expected);
}
TEST(sromTest512,testMul1)
{
    GF2 A("f01327c24a59ce5b5fef9dcb98afb2f9c18bbaadd8fa");
    GF2 B("881b59763c21011d3c0359924251f014c4d8e9b3dcfc");
    GF2 res = A*B;
    string actual = res.convert64bitToHex();
    string expected = "2e5779473480a9a58727a0243ceb8da95861b0d3e938";

    EXPECT_EQ(actual,expected);
}
TEST(sromTest512,tesTrace1)
{
    GF2 A("f01327c24a59ce5b5fef9dcb98afb2f9c18bbaadd8fa");

    int actual = A.Trace();
    int expected = 1;

    EXPECT_EQ(actual,expected);
}
TEST(sromTest512,tesPow1)
{
    GF2 A("f01327c24a59ce5b5fef9dcb98afb2f9c18bbaadd8fa");
    GF2 B("881b59763c21011d3c0359924251f014c4d8e9b3dcfc");
    GF2 res = A^B;
    string actual = res.convert64bitToHex();
    string expected = "194fcfb19de43f69014055f3d59fd37a87855312add95";

    EXPECT_EQ(actual,expected);
}
TEST(sromTest512,testInverse1)
{
    GF2 A("f01327c24a59ce5b5fef9dcb98afb2f9c18bbaadd8fa");

    string actual = A.inverseGF().convert64bitToHex();
    string expected = "91f1b90ffedf0421dcf799b78a89b2ac0802371030c7";

    EXPECT_EQ(actual,expected);
}

TEST(sromTest512,testSum2)
{
    GF2 A("5f1ab2d2f6897911a2004159cab4afcf7c4229f624cf");
    GF2 B("9d3ca8144df69447c8b59ae9f84c8d3c7ad63f14a327");

    A += B;
    string actual = A.convert64bitToHex();
    string expected = "c2261ac6bb7fed566ab5dbb032f822f3069416e287e8";

    EXPECT_EQ(actual,expected);
}
TEST(sromTest512,testInverse2)
{
    GF2 A("5f1ab2d2f6897911a2004159cab4afcf7c4229f624cf");

    string actual = A.inverseGF().convert64bitToHex();
    string expected = "7e77895b3d1a04f9c610a00da260a4eb75e60f163c0c3";

    EXPECT_EQ(actual,expected);
}
TEST(sromTest512,testMul2)
{
    GF2 A("5f1ab2d2f6897911a2004159cab4afcf7c4229f624cf");
    GF2 B("9d3ca8144df69447c8b59ae9f84c8d3c7ad63f14a327");
    GF2 res = A*B;
    string actual = res.convert64bitToHex();

    string expected = "337d9308e8a78374ca2329bd9e769d301f390b86fae3d";

    EXPECT_EQ(actual,expected);
}
TEST(sromTest512,tesTrace2)
{
    GF2 A("5f1ab2d2f6897911a2004159cab4afcf7c4229f624cf");

    int actual = A.Trace();
    int expected = 1;

    EXPECT_EQ(actual,expected);
}


TEST(sromTest512,tesPow2)
{
    GF2 A("5f1ab2d2f6897911a2004159cab4afcf7c4229f624cf");
    GF2 B("9d3ca8144df69447c8b59ae9f84c8d3c7ad63f14a327");
    GF2 res = A^B;
    string actual = res.convert64bitToHex();
    string expected = "34aa84422df2734d6421a35270928337e2e4c50d33dc2";

    EXPECT_EQ(actual,expected);
}
