#include <iostream>
#include <bitset>
int decoder(std::bitset<8> p,std::bitset<4> &bits)
{
    bool A,B,C,D;
    A = (p[7] + p[6] + p[2]+ p[0])%2;
    B = (p[6] + p[5] + p[4]+ p[0])%2;
    C = (p[6] + p[4] + p[3]+ p[2])%2;
    D = (p[7] + p[6] + p[5]+ p[4] + p[3] + p[2] + p[1]+ p[0])%2;

    int k = 0;
    if(A&&B&&C&&D)
    {
        k=1;
    }

    else if(A&&B&&C&&!D)
    {
        p[1]= 1 - p[1];
        k=2;
    }

    else if((!A || !B || !C)&&D)
    {
        k=3;
    }
    else if((!A || !B || !C)&&!D)
    {
        if (!A && B && C) {p[7]= 1 - p[7];}
        if (!A && !B && !C) {p[6]= 1 - p[6];}
        if (A && !B && C) {p[5]= 1 - p[5];}
        if (A && !B && !C) {p[4]= 1 - p[4];}
        if (A && B && !C) {p[3]= 1 - p[3];}
        if (!A && B && !C) {p[2]= 1 - p[2];}
        if (!A && !B && C) {p[0]= 1 - p[0];}
        k=4;
    }

    if(k!=3)
    {
        int z = 0;
        for (int i = 0; i < 8; i+=2)
        {
            bits[z] = p[i];
            z++;
        }

    }

    return k;

}
std::bitset<8> convert(uint16_t c,int &k1,int &k2)
{
    std::bitset<8> first(c);
    c = c>>8;
    std::bitset<8> second(c);

    std::bitset<4> res1;
    std::bitset<4> res2;

    k1 = decoder(first,res1);
    k2 = decoder(second,res2);

    std::bitset<8> otv;

    for(int j=0;j<4;j++)
    {
        otv[j]=res1[j];
    }
    for(int j=4;j<8;j++)
    {
         otv[j]=res2[j-4];
    }
    if(k1==3||k2==3)
    {
        otv= 0b00000000;
    }
    return otv;
}

