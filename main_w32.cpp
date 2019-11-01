#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "lut.h"
using namespace std;



struct W32 //32bit word
{
    uint8_t w0;
    uint8_t w1;
    uint8_t w2;
    uint8_t w3;
};

void printf(W32* var)
{
    printf("%i\n",var->w0);
    printf("%i\n",var->w1);
    printf("%i\n",var->w2);
    printf("%i\n",var->w3);
}
void printb(uint8_t c)
{
    printf("%i = ",c);
    for(uint8_t i=0;i<8;i++)printf("%i",(c&(1<<(7-i)))/(1<<(7-i)));
    printf("\n");
}
void printfb(W32* var)
{
    printb(var->w0);
    printb(var->w1);
    printb(var->w2);
    printb(var->w3);
    printf("\n");
}

void printhex(W32* var)
{

    printf("%02X",var->w0);
    printf("%02X",var->w1);
    printf("%02X",var->w2);
    printf("%02X",var->w3);
    printf("\n");

}
void printhexl(W32* var)
{

    printf("%02X",var[0].w0);
    printf("%02X",var[1].w0);
    printf("%02X",var[2].w0);
    printf("%02X",var[3].w0);

    printf("%02X",var[0].w1);
    printf("%02X",var[1].w1);
    printf("%02X",var[2].w1);
    printf("%02X",var[3].w1);

    printf("%02X",var[0].w2);
    printf("%02X",var[1].w2);
    printf("%02X",var[2].w2);
    printf("%02X",var[3].w2);

    printf("%02X",var[0].w3);
    printf("%02X",var[1].w3);
    printf("%02X",var[2].w3);
    printf("%02X",var[3].w3);

    printf("\n");
}

W32 *SubWord(W32 *a,W32 *b)
{

    *b={sbox[((a->w0)&(0xf0))>>4][(a->w0)&0x0f],sbox[(a->w1&0xf0)>>4][a->w1&0x0f],sbox[(a->w2&0xf0)>>4][a->w2&0x0f],sbox[(a->w3&0xf0)>>4][a->w3&0x0f]};
    return b;
}

W32 *RotWord(W32 *a,W32 *b)
{
    *b={a->w1,a->w2,a->w3,a->w0};
    return b;
}
W32 *Xor(W32 *a,W32 *b,W32 *c)
{
    *c={(a->w0)^(b->w0),(a->w1)^(b->w1),(a->w2)^(b->w2),(a->w3)^(b->w3)};
    return c;
}
void subbytes(W32* a)
{
    for(uint8_t i=0;i<4;i++)SubWord(&a[i],&a[i]);
}

void shiftrow(W32 *a,uint8_t u)
{
    uint8_t temp=a->w0;
    uint8_t temp1=a->w1;
    switch(u)
    {
        case 1:
            a->w0=a->w1;
            a->w1=a->w2;
            a->w2=a->w3;
            a->w3=temp;
            break;

        case 2:
            a->w0=a->w2;
            a->w1=a->w3;
            a->w2=temp;
            a->w3=temp1;
            break;

        case 3:
            a->w0=a->w3;
            a->w3=a->w2;
            a->w2=a->w1;
            a->w1=temp;
            break;
        default:
            break;
    }

}
void tem(W32 *temp,W32 *ekey,uint8_t i) //44x4
{
    switch(i%4)
    {
        case(0):
            temp->w0=ekey[(i-i%4)/4].w0;
            temp->w1=ekey[(i-i%4)/4+1].w0;
            temp->w2=ekey[(i-i%4)/4+2].w0;
            temp->w3=ekey[(i-i%4)/4+3].w0;
            break;

        case(1):
            temp->w0=ekey[(i-i%4)/4].w1;
            temp->w1=ekey[(i-i%4)/4+1].w1;
            temp->w2=ekey[(i-i%4)/4+2].w1;
            temp->w3=ekey[(i-i%4)/4+3].w1;
            break;

        case(2):
            temp->w0=ekey[(i-i%4)/4].w2;
            temp->w1=ekey[(i-i%4)/4+1].w2;
            temp->w2=ekey[(i-i%4)/4+2].w2;
            temp->w3=ekey[(i-i%4)/4+3].w2;
            break;

        case(3):
            temp->w0=ekey[(i-i%4)/4].w3;
            temp->w1=ekey[(i-i%4)/4+1].w3;
            temp->w2=ekey[(i-i%4)/4+2].w3;
            temp->w3=ekey[(i-i%4)/4+3].w3;
            break;
        default:
            break;
    }
}
void item(W32 *ekey,W32 *temp,uint8_t i)
{
    ekey[i].w0=temp->w0;
    ekey[i].w1=temp->w1;
    ekey[i].w2=temp->w2;
    ekey[i].w3=temp->w3;
}

void transpose(W32 *mat)
{
    W32 temp;
    temp=mat[0];
    mat[0]={mat[0].w0,mat[1].w0,mat[2].w0,mat[3].w0};
    mat[1].w0=temp.w1;
    mat[2].w0=temp.w2;
    mat[3].w0=temp.w3;

    temp=mat[1];
    mat[1].w2=mat[2].w1;
    mat[1].w3=mat[3].w1;
    mat[2].w1=temp.w2;
    mat[3].w1=temp.w3;


    temp=mat[2];

    mat[2].w3=mat[3].w2;
    mat[3].w2=temp.w3;
}

void key_schedule(W32 *key,W32 *ekey)
{
    uint8_t N=4;
    uint8_t R=11;
    W32 rconi;
    W32 temp1;
    W32 temp2;
    W32 temp3;

    for(uint8_t i=0;i<4*R;i++)
        {
            if(i<N)
            {
                ekey[i]=key[i];

            }else if(i>=N && i%N==0)
            {

                rconi={rcon[i/N-1],0,0,0};

                temp1=ekey[i-1];
                /*printf("i = %i\n",i);
                printf("temp = ");
                printhex(&temp1);
                */

                RotWord(&temp1,&temp3);

                //printf("RotWord = ");
                //printhex(&temp3);

                //printf("SubWord = ");
                SubWord(&temp3,&temp3);
                //printhex(&temp3);
                //printf("R XOR = ");
                Xor(&temp3,&rconi,&temp3);
                //printhex(&temp3);

                temp2=ekey[i-N];
                //printf("Xor = ");
                Xor(&temp2,&temp3,&temp3);
                //printhex(&temp3);

                ekey[i]=temp3;


            }else if(i>=N && N>6 && i%N==4) //Never used for AES-128
            {
                //Xor(&ekey[i-N],SubWord(&ekey[i-1],&ekey[i]),&ekey[i]);

            }else
            {
                //printf("i = %i\n",i);
                //printf("ekey = ");
                //for(uint8_t k=0;k<8;k++)printhex(&ekey[k]);
                //printf("\n");

                //printf("W[i-1] = ");
                temp1=ekey[i-1];
                //printhex(&temp1);

                //printf("W[i-Nk] = ");
                temp2=ekey[i-N];
                //printhex(&temp2);

                Xor(&temp2,&temp1,&temp3);
                ekey[i]=temp3;
                //printf("Xor  = ");

                //printhex(&temp3);
            }
        }

        //for(uint8_t i=0;i<44;i++)printhex((W32*)&ekey[i]);

}
void add_roundkey(W32 *state,W32 *subk)
{
    for(uint8_t i=0;i<4;i++)
        {
            Xor(&state[i],&subk[i],&state[i]);
        }
}
void shiftrows(W32 *state)
{
    for(uint8_t i=1;i<4;i++)
        {
            shiftrow(&state[i],i);
        }
}

void mixcolumns(W32 *state)
{
    W32 temp[4]={state[0],state[1],state[2],state[3]};
    state[0].w0=glp2[temp[0].w0]^glp3[temp[1].w0]^temp[2].w0^temp[3].w0;
    state[1].w0=glp2[temp[1].w0]^glp3[temp[2].w0]^temp[0].w0^temp[3].w0;
    state[2].w0=glp2[temp[2].w0]^glp3[temp[3].w0]^temp[0].w0^temp[1].w0;
    state[3].w0=glp2[temp[3].w0]^glp3[temp[0].w0]^temp[1].w0^temp[2].w0;

    state[0].w1=glp2[temp[0].w1]^glp3[temp[1].w1]^temp[2].w1^temp[3].w1;
    state[1].w1=glp2[temp[1].w1]^glp3[temp[2].w1]^temp[0].w1^temp[3].w1;
    state[2].w1=glp2[temp[2].w1]^glp3[temp[3].w1]^temp[0].w1^temp[1].w1;
    state[3].w1=glp2[temp[3].w1]^glp3[temp[0].w1]^temp[1].w1^temp[2].w1;

    state[0].w2=glp2[temp[0].w2]^glp3[temp[1].w2]^temp[2].w2^temp[3].w2;
    state[1].w2=glp2[temp[1].w2]^glp3[temp[2].w2]^temp[0].w2^temp[3].w2;
    state[2].w2=glp2[temp[2].w2]^glp3[temp[3].w2]^temp[0].w2^temp[1].w2;
    state[3].w2=glp2[temp[3].w2]^glp3[temp[0].w2]^temp[1].w2^temp[2].w2;

    state[0].w3=glp2[temp[0].w3]^glp3[temp[1].w3]^temp[2].w3^temp[3].w3;
    state[1].w3=glp2[temp[1].w3]^glp3[temp[2].w3]^temp[0].w3^temp[3].w3;
    state[2].w3=glp2[temp[2].w3]^glp3[temp[3].w3]^temp[0].w3^temp[1].w3;
    state[3].w3=glp2[temp[3].w3]^glp3[temp[0].w3]^temp[1].w3^temp[2].w3;
}

int main(int argc,char **argv)
{
    uint8_t nrounds=10;//10 rounds ,AES-128
    //AES S-box


    while ( *argv ) printf( "%s\n", *argv++ );

    W32 key_32[4]={ {0x00,0x01,0x02,0x03},
                    {0x04,0x05,0x06,0x07},
                    {0x08,0x09,0x0a,0x0b},
                    {0x0c,0x0d,0x0e,0x0f}};



    //W32 key_32[4]={ {0x2b,0x7e,0x15,0x16},{0x28,0xae,0xd2,0xa6},{0xab,0xf7,0x15,0x88},{0x09,0xcf,0x4f,0x3c}};
    //W32 plaintext[4]={{0x32,0x43,0xf6,0xa8},{0x88,0x5a,0x30,0x8d},{0x31,0x31,0x98,0xa2},{0xe0,0x37,0x07,0x34}};

    W32 plaintext[4]={  {0x00,0x11,0x22,0x33},
                        {0x44,0x55,0x66,0x77},
                        {0x88,0x99,0xaa,0xbb},
                        {0xcc,0xdd,0xee,0xff}};

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

    W32 ekey_32[44]={0};

    transpose(plaintext);


    printf("PLAINTEXT\n");
    //for(uint8_t i=0;i<4;i++)printhex(&plaintext[i]);
    printhexl(plaintext);
    printf("\n");

    printf("KEY\n");
    printhexl(key_32);
    printf("\n");




    //for(uint8_t i=0;i<4;i++)printhex(&key_32[i]);

    printf("\n");
    printf("\n");
    printf("\n");
    printf("round[0].input  ");
    printhexl(plaintext);

    //for(uint8_t i=0;i<4;i++)printhex(&plaintext[i]);
    printf("\n");




    key_schedule((W32*)key_32,(W32*)ekey_32);

    for(uint8_t i=0;i<11;i++)transpose(&ekey_32[4*i]);

    printf("MAIN\n");
    //for(uint8_t i=0;i<44;i++)printhex((W32*)&ekey_32[i]);
    printf("round[0].k_sch  ");
    printhexl(&key_32[0]);
    printf("\n");

    add_roundkey((W32*)plaintext,(W32*)ekey_32);

    //for(uint8_t i=0;i<4;i++)printhex((W32*)&ekey_32[i]);


    for(uint8_t r=1;r<nrounds;r++)
        {
            printf("round[%i].start  ",r);
            //for(uint8_t i=0;i<4;i++)printhex(&plaintext[i]);
            printhexl(plaintext);
            printf("\n");

            printf("round[%i].s_box  ",r);
            subbytes(plaintext);

            //for(uint8_t i=0;i<4;i++)printhex(&plaintext[i]);
            printhexl(plaintext);
            printf("\n");

            printf("round[%i].s_row  ",r);
            shiftrows(plaintext);
            //for(uint8_t i=0;i<4;i++)printhex(&plaintext[i]);
            printhexl(plaintext);
            printf("\n");


            printf("round[%i].m_col  ",r);
            mixcolumns(plaintext);
            //for(uint8_t i=0;i<4;i++)printhex(&plaintext[i]);
            printhexl(plaintext);
            printf("\n");

            printf("round[%i].k_sch  ",r);
            //for(uint8_t i=0;i<4;i++)printhex((W32*)&ekey_32[4*r+i]);
            printhexl(&ekey_32[4*r]);
            printf("\n");
            add_roundkey((W32*)plaintext,(W32*)&ekey_32[4*r]);

        }

    subbytes((W32*)&plaintext);

    shiftrows((W32*)&plaintext);

    add_roundkey((W32*)&plaintext,(W32*)&ekey_32[4*nrounds]);

    printf("\n");
    printf("\n");
    printf("CIPHER\n");
    //for(uint8_t i=0;i<4;i++)printhex(&plaintext[i]);
    printhexl(plaintext);
    printf("\n");
    printf("------------------------\n");

    //for(uint8_t i=0;i<44;i++)printfb(&ekey_32[i]);
    return 0;
}
