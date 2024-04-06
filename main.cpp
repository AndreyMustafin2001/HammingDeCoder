#include "hammingdecoder.cpp"
#include <gtest/gtest.h>
#include <bitset>
uint8_t b = {0b10100100};//1100111010010010
TEST(F,A)
{
    uint16_t a1 = {0b1100111010010010};


    int k1,k2;
    std::bitset<8> otv;

    otv = convert(a1,k1,k2);
    ASSERT_EQ(otv,b);
    ASSERT_EQ(k1,1);//No Errors , k = 1 .
    ASSERT_EQ(k2,1);//No Errors , k = 1 .
    }
TEST(F2,A)
{
    uint16_t a1 = {0b1100111010010000};
    int k1,k2;
    std::bitset<8> otv;

    otv = convert(a1,k1,k2);
    ASSERT_EQ(otv,b);
    ASSERT_EQ(k1,2);//Single Error in p4 , k = 2 .
    ASSERT_EQ(k2,1);//No Errors , k = 1 .
}
TEST(F3,A)
{
    uint16_t a1 = {0b1110111011010010};
    int k1,k2;
    std::bitset<8> otv;

    otv = convert(a1,k1,k2);
    ASSERT_EQ(otv,b);
    ASSERT_EQ(k1,4);//Single Error  , k = 4 .
    ASSERT_EQ(k2,4);//Single Error  , k = 4 .
}
TEST(F4,A)
{
    uint16_t a1 = {0b1100111010011110};
    uint8_t c = 0b00000000;
    int k1,k2;
    std::bitset<8> otv;

    otv = convert(a1,k1,k2);
    ASSERT_EQ(otv,c);
    ASSERT_EQ(k1,3);//Double Error  , k = 4 .
    ASSERT_EQ(k2,1);//No Error  , k = 1 .
}
int main(int argc,char* argv[])
{
   testing::InitGoogleTest(&argc,argv);
   return RUN_ALL_TESTS();
}
