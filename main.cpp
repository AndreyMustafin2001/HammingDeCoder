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
    if(k==1)
    {
        std::cout<<"No errors"<<std::endl;
    }
    else if(k==2)
    {
        std::cout<<"Single error in p4"<<std::endl;
    }
    else if(k==3)
    {
        std::cout<<"Double error!"<<std::endl;
    }
    else if(k==4)
    {
        std::cout<<"Single error!"<<std::endl;

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
std::bitset<8> convert(uint16_t c)
{
    std::bitset<8> first(c);
    c = c>>8;
    std::bitset<8> second(c);

    std::bitset<4> res1;
    std::bitset<4> res2;

    int k1 = decoder(first,res1);
    for(int i=3;i>=0;--i)
    {
        std::cout<<res1[i];
    }
    std::cout << std::endl;
    int k2 = decoder(second,res2);
    for(int i=3;i>=0;--i)
    {
        std::cout<<res2[i];
    }
    std::cout << std::endl;
    std::bitset<8> otv;
    for(int j=0;j<4;j++)
    {
        otv[j]=res1[j];
    }
    for(int j=4;j<8;j++)
    {
         otv[j]=res2[j-4];
    }
    return otv;
}
int main()
{
                    //1100111010010010//10100100
    uint16_t c = 0b1100111010010010;//No errors/No errors
    //uint16_t c = 0b1100111010010000;//Single error in p4/No errors
    //uint16_t c = 0b1110111010010010;//No errors /Single error
    //uint16_t c = 0b1100111111011010;//Double error/ single error
    std::bitset<8> otv;
    otv = convert(c);

    for(int i=7;i>=0;--i)
    {
        std::cout<<otv[i];
    }
    std::cout << std::endl;


	return 0;
}
