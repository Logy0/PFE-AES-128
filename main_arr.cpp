#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "lut.h"
using namespace std;

typedef uint8_t u8;

void printf(u8* var)
{
    for(u8 k=0;k<4;k++){
        for(u8 i=0;i<4;i++)
            printf("%i \n",var[4*k+i]);
        printf("\n");
    }
}
void printb(uint8_t c)
{
    printf("%i = ",c);

    for(uint8_t i=0;i<8;i++)printf("%i",(c&(1<<(7-i)))/(1<<(7-i)));
    printf("\n");
}
void printfb(u8* var)
{
     for(u8 k=0;k<4;k++){
        for(u8 i=0;i<4;i++)
            printb(var[4*k+i]);
        printf("\n");
    }
    printf("\n");
}

void printhexl(u8* var)
{
    for(u8 k=0;k<4;k++){
        for(u8 i=0;i<4;i++)
            printf("%02X",var[4*i+k]);
    }
    printf("\n");
}
void cp(u8 *a,u8 *b)
{
    for(u8 i=0;i<4;i++)
        b[i]=a[i];
}
u8 *RotWord(u8 *a)
{
    u8 temp=a[0];
    a[0]=a[1];
    a[1]=a[2];
    a[2]=a[3];
    a[3]=temp;
    return a;
}
u8 *SubWord(u8 *a)
{
     for(u8 i=0;i<4;i++){
        a[i]=sbox[(a[i]&0xf0)>>4][a[i]&0x0f];
    }
    return a;
}
u8 *Xor(u8 *a,u8 *b)
{
    for(u8 k=0;k<4;k++){
            b[k]=a[k]^b[k];
    }
    return b;
}
void subbytes(u8* a)
{
    for(u8 k=0;k<4;k++){
        for(u8 i=0;i<4;i++){
            a[4*k+i]=sbox[((a[4*k+i])&(0xf0))>>4][(a[4*k+i])&0x0f];
        }
    }
}

void shiftrow(u8 *a)
{
    uint8_t temp[16];
    for(u8 i=0;i<16;i++)temp[i]=a[i];

    for(u8 k=0;k<4;k++){
        for(u8 i=0;i<4;i++){
            a[4*k+i]=temp[4*k+(i+k)%4];
        }
    }
}
void transpose(u8 *a)
{
    uint8_t temp[16];
    for(u8 i=0;i<16;i++)temp[i]=a[i];

    for(u8 k=0;k<4;k++){
        for(u8 i=0;i<4;i++){
            a[4*k+i]=temp[4*i+k];
        }
    }
}


void key_schedule(u8 *key,u8 *ekey)
{
    uint8_t N=4;
    uint8_t R=11;
    u8 rconi[4]={0,0,0,0};
    u8 temp1[4];

    for(uint8_t i=0;i<N;i++)
        {
            for(u8 k=0;k<4;k++)ekey[i*4+k]=key[i*4+k];
        }
    for(u8 i=N;i<4*R;i++){
        if(i>=N && i%N==0)
            {
                rconi[0]=rcon[i/N-1];
                cp(&ekey[(i-1)*4],&ekey[i*4]);
                SubWord(RotWord(&ekey[i*4]));
                Xor(rconi,&ekey[i*4]);
                cp(&ekey[(i-N)*4],temp1);
                Xor(temp1,&ekey[i*4]);

            }else if(i>=N && N>6 && i%N==4) //Never used for AES-128
            {
                cp(&ekey[i-1],&ekey[i]);
                Xor(&ekey[i-N],SubWord(&ekey[i]));

            }else
            {
                cp(&ekey[(i-1)*4],&ekey[i*4]);
                cp(&ekey[(i-N)*4],temp1);
                Xor(temp1,&ekey[i*4]);
            }
        }
}
void add_roundkey(u8 *state,u8 *subk)
{
    for(uint8_t i=0;i<4;i++)
        {
            Xor(&subk[4*i],&state[4*i]);
        }
}


void mixcolumns(u8 *state)
{
    u8 temp[16];
    for(u8 i=0;i<16;i++)temp[i]=state[i];

    for(u8 k=0;k<4;k++)
    {
        for(u8 i=0;i<4;i++)
            {
                state[4*i+k]=glp2[temp[4*i+k]]^glp3[temp[((1+i)%4)*4+k]]^temp[((2+i)%4)*4+k]^temp[((3+i)%4)*4+k];
            }
    }
}
void AES_128_dbg(u8 *plaintext,u8 *key_32)
{


    uint8_t nrounds=10;//10 rounds ,AES-128
    //AES S-box
    u8 ekey_32[176]={0};

    transpose(plaintext);



    printf("MAIN\n");

    printf("round[0].input  ");
    printhexl(plaintext);
    printf("\n");

    key_schedule((u8*)key_32,(u8*)ekey_32);

    for(uint8_t i=0;i<11;i++)transpose(&ekey_32[16*i]);



    printf("round[0].k_sch  ");
    printhexl(&key_32[0]);
    printf("\n");




    add_roundkey((u8*)plaintext,(u8*)ekey_32);



    for(uint8_t r=1;r<nrounds;r++)
        {
            printf("round[%i].start  ",r);
            printhexl(plaintext);
            printf("\n");

            printf("round[%i].s_box  ",r);
            subbytes(plaintext);
            printhexl(plaintext);
            printf("\n");

            printf("round[%i].s_row  ",r);
            shiftrow(plaintext);
            printhexl(plaintext);
            printf("\n");


            printf("round[%i].m_col  ",r);
            mixcolumns(plaintext);
            printhexl(plaintext);
            printf("\n");

            printf("round[%i].k_sch  ",r);
            printhexl(&ekey_32[16*r]);
            printf("\n");
            add_roundkey((u8*)plaintext,(u8*)&ekey_32[16*r]);

        }

    printf("round[10].start  ");
    printhexl(plaintext);
    printf("\n");

    printf("round[10].s_box  ");
    subbytes(plaintext);
    printhexl(plaintext);
    printf("\n");


    printf("round[10].s_row  ");
    shiftrow(plaintext);
    printhexl(plaintext);
    printf("\n");

    printf("round[10].k_sch  ");
    printhexl(&ekey_32[16*nrounds]);
    printf("\n");
    add_roundkey((u8*)plaintext,(u8*)&ekey_32[16*nrounds]);

    printf("\n");
    printf("\n");
}

void AES_128(u8 *plaintext,u8 *key_32)
{
    uint8_t nrounds=10;//10 rounds ,AES-128
    //AES S-box
    u8 ekey_32[176]={0};

    transpose(plaintext);

    key_schedule((u8*)key_32,(u8*)ekey_32);

    for(uint8_t i=0;i<11;i++)transpose(&ekey_32[16*i]);

    add_roundkey((u8*)plaintext,(u8*)ekey_32);



    for(uint8_t r=1;r<nrounds;r++)
        {
            subbytes(plaintext);
            shiftrow(plaintext);
            mixcolumns(plaintext);
            add_roundkey((u8*)plaintext,(u8*)&ekey_32[16*r]);
        }
    subbytes(plaintext);
    shiftrow(plaintext);
    add_roundkey((u8*)plaintext,(u8*)&ekey_32[16*nrounds]);
}


void AES_128_CBC(u8 *plaintext,u8 *key_32,u8 *IV,uint32_t nblocks)
{
    u8 lastcipher[16];
    transpose(IV);

    for(u8 i=0;i<16;i++)lastcipher[i]=IV[i];
    for(uint32_t k=0;k<nblocks;k++)
    {
        add_roundkey(plaintext,lastcipher);
        AES_128(&plaintext[k*16],key_32);
        for(u8 i=0;i<16;i++)lastcipher[i]=plaintext[16*k+i];
    }
}
int main(int argc,char **argv)
{

    while ( *argv ) printf( "%s\n", *argv++ );
    printf("\n");

    u8 key_32[16]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
    u8 plaintext[16]={0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
    u8 IV[16]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    //u8 key_32[4]={ {0x2b,0x7e,0x15,0x16},{0x28,0xae,0xd2,0xa6},{0xab,0xf7,0x15,0x88},{0x09,0xcf,0x4f,0x3c}};
    //u8 plaintext[4]={{0x32,0x43,0xf6,0xa8},{0x88,0x5a,0x30,0x8d},{0x31,0x31,0x98,0xa2},{0xe0,0x37,0x07,0x34}};

    /*
    u8 plaintext[4]={0x6b,0x2e,0xe9,0x73,0xc1,0x40,0x3d,0x93,0xbe,0x9f,0x7e,0x17,0xe2,0x96,0x11,0x2a}; //16 bytes of plaintext
    //u8 plaintext[4]={{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}}; //16 bytes of plaintext
    //u8 plaintext[4]={{219,242,1,198},{19,10,1,198},{83,34,1,198},{69,92,1,198}}; //16 bytes of plaintext

    u8 key_32[4]={0x2b,0x28,0xab,0x09,0x7e,0xae,0xf7,0xcf,0x15,0xd2,0x15,0x4f,0x16,0xa6,0x88,0x3c};
    */

    printf("PLAINTEXT\n");
    for(u8 i=0;i<16;i++)printf("%02X",plaintext[i]);
    printf("\n");
    printf("\n");

    printf("KEY\n");
    for(u8 i=0;i<16;i++)printf("%02X",key_32[i]);

    printf("\n");
    printf("\n");

    AES_128_CBC(plaintext,key_32,IV,1);

    printf("CIPHER\n");
    printhexl(plaintext);
    printf("\n");
    printf("------------------------\n");
    return 0;
}
