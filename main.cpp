#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "lut.h"
using namespace std;

uint8_t rcon[10]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36};
uint8_t sbox[16][16]= {{0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
                       {0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
                       {0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
                       {0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75},
                       {0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84},
                       {0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf},
                       {0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8},
                       {0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2},
                       {0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73},
                       {0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb},
                       {0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79},
                       {0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08},
                       {0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a},
                       {0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e},
                       {0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf},
                       {0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16}};


void printf(uint8_t* var)
{
    for(uint8_t i=0;i<4;i++)printf("%i\n",var[i]);

}
void printb(uint8_t c)
{
    printf("%i = ",c);
    for(uint8_t i=0;i<8;i++)printf("%i",(c&(1<<(7-i)))/(1<<(7-i)));
    printf("\n");
}
void printfb(uint8_t* var)
{
    for(uint8_t i=0;i<4;i++)printb(var[i]);
}

void printhex(uint8_t* var)
{
    for(uint8_t i=0;i<4;i++)printf("%02X",var[i]);
    printf("\n");

}

uint8_t *SubWord(uint8_t *a,uint8_t *b)
{
    for(uint8_t i=0;i<4;i++)b[i]=sbox[(a[i]&0xf0)>>4][a[i]&0x0f];
    return b;
}

uint8_t *RotWord(uint8_t *a,uint8_t *b)
{
    for(uint8_t i=0;i<4;i++)b[i]=a[(i+1)%4];
    return b;
}
uint8_t *Xor(uint8_t *a,uint8_t *b,uint8_t *c)
{
    for(uint8_t i=0;i<4;i++)c[i]=a[i]^b[i];
    return c;
}
void subbytes(uint8_t **a)
{
    for(uint8_t i=0;i<4;i++)SubWord(a[i],a[i]);
}
void shiftrow(uint8_t *a,uint8_t u)
{
    uint8_t temp=a[0];
    uint8_t temp1=a[1];
    switch(u)
    {
        case 1:
            a[0]=a[1];
            a[1]=a[2];
            a[2]=a[3];
            a[3]=temp;
            break;

        case 2:
            a[0]=a[2];
            a[1]=a[3];
            a[2]=temp;
            a[3]=temp1;
            break;

        case 3:
            a[0]=a[3];
            a[3]=a[2];
            a[2]=a[1];
            a[1]=temp;
            break;
        default:
            break;
    }

}
void key_schedule(uint8_t key[][4], uint8_t ekey[][44])
{
    uint8_t N=4;
    uint8_t R=11;
    uint8_t rconi[4]={0,0,0,0};

    for(uint8_t i=0;i<4*R;i++)
        {
            if(i<N)
            {
                for(uint8_t k=0;k<4;k++)
                    {
                        ekey[k][i]=key[k][i];
                    }
                printf("2\n");
            }
            else if(i>=N && i%N==0)
            {

                rconi[0]=rcon[i/N-1];
                printf("i = %i\n",i);
                printf("temp = ");


                RotWord(ekey[i-1],ekey[i]);
                SubWord(ekey[i],ekey[i]);
                Xor(ekey[i-N],ekey[i],ekey[i]);
                Xor(ekey[i],rconi,ekey[i]);



                printf("1\n");
            }else if(i>=N && N>6 && i%N==4) //Never used for AES-128
            {
                Xor(ekey[i-N],SubWord(ekey[i-1],ekey[i]),ekey[i]);

            }else
            {
                Xor(ekey[i-N],ekey[i-1],ekey[i]);
            }

        }



}
void add_roundkey(uint8_t **state,uint8_t *subk)
{
    for(uint8_t i=0;i<4;i++)
        {
            Xor(state[i],&subk[i],state[i]);
        }
}
void shiftrows(uint8_t **state)
{
    for(uint8_t i=1;i<4;i++)
        {
            shiftrow(state[i],i);
        }
}

void mixcolumns(uint8_t **state)
{
    uint8_t temp[4][4];
    for(uint8_t k=0;k<4;k++)
        for(uint8_t i=0;i<4;i++)
            temp[k][i]=state[k][i];
    state[0][0]=glp2[temp[0][0]]^glp3[temp[1][0]]^temp[2][0]^temp[3][0];
    state[1][0]=glp2[temp[1][0]]^glp3[temp[2][0]]^temp[0][0]^temp[3][0];
    state[2][0]=glp2[temp[2][0]]^glp3[temp[3][0]]^temp[0][0]^temp[1][0];
    state[3][0]=glp2[temp[3][0]]^glp3[temp[0][0]]^temp[1][0]^temp[2][0];

    state[0][1]=glp2[temp[0][1]]^glp3[temp[1][1]]^temp[2][1]^temp[3][1];
    state[1][1]=glp2[temp[1][1]]^glp3[temp[2][1]]^temp[0][1]^temp[3][1];
    state[2][1]=glp2[temp[2][1]]^glp3[temp[3][1]]^temp[0][1]^temp[1][1];
    state[3][1]=glp2[temp[3][1]]^glp3[temp[0][1]]^temp[1][1]^temp[2][1];

    state[0][2]=glp2[temp[0][2]]^glp3[temp[1][2]]^temp[2][2]^temp[3][2];
    state[1][2]=glp2[temp[1][2]]^glp3[temp[2][2]]^temp[0][2]^temp[3][2];
    state[2][2]=glp2[temp[2][2]]^glp3[temp[3][2]]^temp[0][2]^temp[1][2];
    state[3][2]=glp2[temp[3][2]]^glp3[temp[0][2]]^temp[1][2]^temp[2][2];

    state[0][3]=glp2[temp[0][3]]^glp3[temp[1][3]]^temp[2][3]^temp[3][3];
    state[1][3]=glp2[temp[1][3]]^glp3[temp[2][3]]^temp[0][3]^temp[3][3];
    state[2][3]=glp2[temp[2][3]]^glp3[temp[3][3]]^temp[0][3]^temp[1][3];
    state[3][3]=glp2[temp[3][3]]^glp3[temp[0][3]]^temp[1][3]^temp[2][3];
}

int main(int argc,char **argv)
{
    uint8_t nrounds=10;//10 rounds ,AES-128
    //AES S-box
    /*
    W32 key_32[4]={ {0x00,0x04,0x08,0x0c},
                    {0x01,0x05,0x09,0x0d},
                    {0x02,0x06,0x0a,0x0e},
                    {0x03,0x07,0x0b,0x0f}};
    */


    uint8_t key_32[4][4]={ {0x2b,0x28,0xab,0x09},
                            {0x7e,0xae,0xf7,0xcf},
                            {0x15,0xd2,0x15,0x4f},
                            {0x16,0xa6,0x88,0x3c}};


    uint8_t plaintext[4][4]={{0x00,0x44,0x88,0xcc},
                             {0x11,0x55,0x99,0xdd},
                             {0x22,0x66,0xaa,0xee},
                             {0x33,0x77,0xbb,0xff}};
    /*
    W32 plaintext[4]={{0x6b,0x2e,0xe9,0x73},
                      {0xc1,0x40,0x3d,0x93},
                      {0xbe,0x9f,0x7e,0x17},
                      {0xe2,0x96,0x11,0x2a}}; //16 bytes of plaintext
    //W32 plaintext[4]={{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}}; //16 bytes of plaintext
    //W32 plaintext[4]={{219,242,1,198},{19,10,1,198},{83,34,1,198},{69,92,1,198}}; //16 bytes of plaintext
    W32 key_32[4]={{0x2b,0x28,0xab,0x09},
                   {0x7e,0xae,0xf7,0xcf},
                   {0x15,0xd2,0x15,0x4f},
                   {0x16,0xa6,0x88,0x3c}};
    */
    //W32 key_32[4]={{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};


    uint8_t ekey_32[4][44]={0};
    //=(uint8_t**)malloc(sizeof(uint8_t*)*4);
    //for(uint8_t i=0;i<4;i++)ekey_32[i]=(uint8_t*)malloc(sizeof(uint8_t)*44);

    printf("PLAINTEXT\n");
    for(uint8_t i=0;i<4;i++)printhex((uint8_t*)plaintext[i]);
    printf("\n");
    printf("KEY\n");
    for(uint8_t i=0;i<4;i++)printhex((uint8_t*)key_32[i]);
    printf("\n");
    printf("round[0].input\n");
    for(uint8_t i=0;i<4;i++)printhex((uint8_t*)plaintext[i]);
    printf("\n");



    key_schedule(key_32,ekey_32);

    printf("round[0].k_sch\n");
    for(uint8_t i=0;i<4;i++)
    {
       for(uint8_t k=0;k<44;k++)
        {
            printf("%02X",ekey_32[i][k]);

        }
        printf("\n");
    }

    //add_roundkey(plaintext,ekey_32[0]);

    /*
    for(uint8_t r=1;r<nrounds;r++)
        {
            printf("\n");
            printf("round[%i].start\n",r);
            for(uint8_t i=0;i<4;i++)printhex(plaintext[i]);
            printf("\n");
            printf("round[%i].s_box\n",r);
            subbytes((uint8_t**)plaintext);
            for(uint8_t i=0;i<4;i++)printhex(plaintext[i]);
            printf("\n");

            printf("round[%i].s_row\n",r);
            shiftrows((uint8_t**)plaintext);
            for(uint8_t i=0;i<4;i++)printhex(plaintext[i]);
            printf("\n");
            printf("round[%i].m_col\n",r);
            mixcolumns((uint8_t**)plaintext);
            for(uint8_t i=0;i<4;i++)printhex(plaintext[i]);
            printf("\n");
            printf("round[%i].k_sch\n",r);
            //for(uint8_t i=0;i<4;i++)printhex(ekey_32[i]);
            add_roundkey((uint8_t**)plaintext,ekey_32[4*r]);

        }

    subbytes((uint8_t**)plaintext);
    shiftrows((uint8_t**)plaintext);

    add_roundkey((uint8_t**)plaintext,(uint8_t*)ekey_32[4*nrounds]);

    printf("CIPHER\n");
    for(uint8_t i=0;i<4;i++)printhex((uint8_t*)plaintext[i]);
    printf("------------------------\n");
    */
    //for(uint8_t i=0;i<44;i++)printfb(&ekey_32[i]);
    return 0;
}
