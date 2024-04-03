#include <iostream>
int decoder(uint16_t a,uint8_t &bits)
{
    bool A,B,C,D;
    bool p[16];
    for(int i=0;i<16;i++)
    {
        if(a&(1<<i))
            p[i] = 1;
    }
    A = p[7] + p[6] + p[2]+ p[0];
    B = p[6] + p[5] + p[4]+ p[0];
    C = p[6] + p[4] + p[3]+ p[2];
    D = p[7] + p[6] + p[5]+ p[4] + p[3] + p[2] + p[1]+ p[0];

    int k = 0;
    if(A&&B&&C&&D)
    {
        k=1;
    }

    else if(A&&B&&C&&!D)
    {
        if(p[6]==1)p[6] = 0; else p[6] = 1;
        k=2;
    }

    else if((!A || !B || !C)&&D)
    {
        k=3;
    }
    else if((!A || !B || !C)&&!D)
    {
        std::cout<<"Single error!"<<std::endl;
        if (!A && B && C) {if(p[0]==1)p[0] = 0; else p[0] = 1;}
        if (!A && !B && !C) {if(p[1]==1)p[1] = 0; else p[1] = 1;}
        if (A && !B && C) {if(p[2]==1)p[2] = 0; else p[2] = 1;}
        if (A && !B && !C) {if(p[3]==1)p[3] = 0; else p[3] = 1;}
        if (A && B && !C) {if(p[4]==1)p[4] = 0; else p[4] = 1;}
        if (!A && B && !C) {if(p[5]==1)p[5] = 0; else p[5] = 1;}
        if (!A && !B && C) {if(p[7]==1)p[7] = 0; else p[7] = 1;}
        k=4;
    }
    for(int i=0;i<16;i++)
    {
        if(a&(1<<i))
            p[i] = 1;
    }
    std::cout <<"First Half:"<<std::endl;
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
    bool AA,BB,CC,DD;
    AA = p[15] + p[14] + p[10]+ p[8];
    BB = p[14] + p[13] + p[12]+ p[8];
    CC = p[14] + p[12] + p[11]+ p[10];
    DD = p[15] + p[14] + p[13]+ p[12] + p[11] + p[10] + p[9]+ p[8];

    int f = 0;
    if(AA&&BB&&CC&&DD)
    {
        f=1;
    }

    else if(AA&&BB&&CC&&!DD)
    {
        if(p[14]==1)p[14] = 0; else p[14] = 1;
        f=2;
    }

    else if((!AA || !BB || !CC)&&DD)
    {
        f=3;
    }
    else if((!AA || !BB || !CC)&&!DD)
    {
        std::cout<<"Single error!"<<std::endl;
        if (!AA && BB && CC) {if(p[8]==1)p[8] = 0; else p[8] = 1;}
        if (!AA && !BB && !CC) {if(p[9]==1)p[9] = 0; else p[9] = 1;}
        if (AA && !BB && CC) {if(p[10]==1)p[10] = 0; else p[10] = 1;}
        if (AA && !BB && !CC) {if(p[11]==1)p[11] = 0; else p[11] = 1;}
        if (AA && BB && !CC) {if(p[12]==1)p[12] = 0; else p[12] = 1;}
        if (!AA && BB && !CC) {if(p[13]==1)p[13] = 0; else p[13] = 1;}
        if (!AA && !BB && CC) {if(p[15]==1)p[15] = 0; else p[15] = 1;}
        f=4;
    }

    for(int i=0;i<16;i++)
    {
        if(a&(1<<i))
            p[i] = 1;
    }

    bits = 0b00000000;
    int z = 0;
    for (int i = 0; i < 16; i+=2)
    {
        uint16_t p = 0b00000001;
        p = p << i;
        if(a&p)
        {
            p = 1 << z;
            bits |= p;
        }
        z++;
    }
    std::cout<<"Second Half: "<<std::endl;
    if(f==1)
    {
        std::cout<<"No errors"<<std::endl;
        return 1;
    }
    if(f==2)
    {
        std::cout<<"Single error in p4"<<std::endl;
        return 2;
    }
    if(f==3)
    {
        std::cout<<"Double error!"<<std::endl;
        return 3;
    }
    if(f==4)
    {
        std::cout<<"Single error!"<<std::endl;
        return 4;
    }
}
int main()
{
    uint16_t a = 0b1100111010010010;//10100100
    uint8_t b;
    std::cout<<"Errors: "<<std::endl;
    int error = decoder(a,b);
    for (int i = 7; i >= 0; --i)
        {
            int bit = (b >> i) & 1;
            std::cout << bit;
        }
    std::cout << std::endl;

	return 0;
}
