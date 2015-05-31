#include<stdio.h>
typedef unsigned char byte;
typedef unsigned short halfword;
typedef unsigned int word;
byte Mem0[256];
byte Mem1[256];


word lw(byte addr) {
    word data0,data1,data2,data3;
    byte pos00, pos01 , pos10, pos11;
    
    pos00=(addr+1)/2;
    pos01=(addr+3)/2;
    
    pos10=addr/2;
    pos11=(addr+2)/2;
    
    
    if(addr%2==0){
        data0=Mem0[pos00];
        data1=Mem1[pos10];
        data2=Mem0[pos01];
        data3=Mem1[pos11];
    }
    else if(addr%2==1) {
        data0=Mem1[pos10];
        data1=Mem0[pos00];
        data2=Mem1[pos11];
        data3=Mem0[pos01];
    }
    return (data0<<24)|(data1<<16)|(data2<<8)|(data3);
}

halfword lh(byte addr) {
    byte pos0, pos1, pos2, pos3;
    halfword data0, data1;
    
    pos0=(addr+1)/2;
    pos1=addr/2;
    
    if(addr%2==0){
        data0=Mem0[pos0];
        data1=Mem1[pos1];
    }
    else if(addr%2==1){
        data0=Mem1[pos1];
        data1=Mem0[pos0];
    }
    return (data0<<8)|(data1);
}

byte lb(byte addr) {
    byte data0;
    byte pos;
    
    pos=addr/2;
    
    if(addr%2==0) {
        data0=Mem0[pos];
    }
    else if(addr%2==1) {
        data0=Mem1[pos];
    }
    return data0;
}

void sw(byte addr,word data) {
    byte pos00, pos01, pos10, pos11;
    
    pos00=(addr+1)/2;
    pos01=(addr+3)/2;
    
    pos10=addr/2;
    pos11=(addr+2)/2;
    
    if (addr%2==0) {
        Mem0[pos00]=data>>24;
        Mem1[pos10]=data>>16&0x000000ff;
        Mem0[pos01]=data>>8&0x000000ff;
        Mem1[pos11]=data&0x000000ff;
    }
    else if(addr%2==1) {
        Mem1[pos10]=data>>24;
        Mem0[pos00]=data>>16&0x000000FF;
        Mem1[pos11]=data>>8&0x000000ff;
        Mem0[pos01]=data&0x000000ff;
    }
}
void sh(byte addr,halfword data) {
    byte pos0, pos1;
    
    pos0=(addr+1)/2;
    pos1=addr/2;
    
    if(addr%2==0){
        Mem0[pos0]=data>>8;
        Mem1[pos1]=data&0x00ff;
    }
    else if(addr%2==1){
        Mem1[pos1]=data>>8;
        Mem0[pos0]=data&0x00ff;
    }
    
}
void sb(byte addr,byte data) {
    byte pos;
    pos=addr/2;
    
    if(addr%2==0) {
        Mem0[pos]=data;
    }
    else if(addr%2==1) {
        Mem1[pos]=data;
    }
}

int main(void) {
    sw(0,0x01234567);
    sw(3,0x89abcdef);
    sw(5,0xfedcba98);
    sw(6,0x76543210);
    sw(7,0x01234567);
    sw(14,0x89abcdef);
    
    
    sh(16,0xfedc)
    sh(21,0xba98);
    sh(26,0x7654);
    sh(27,0x3210);
    sh(31,0x0123);
    
    sb(33,0x45);
    sb(34,0x67);
    sb(35,0x89);
    sb(35,0xab);
    sb(34,0xcd);
    printf("0-15:*************************************\n");
    printf("%X\n",lw(0));
    printf("%X\n",lw(3));
    printf("%X\n",lw(6));
    printf("%X\n",lw(7));
    printf("%X\n",lw(9));
    printf("%X\n",lw(14));
    printf("%X\n",lh(8));
    pirntf("%X\n",lh(11));
    printf("%X\n",lh(4));
    printf("%X\n",lh(13));
    printf("%X\n",lb(1));
    printf("%X\n",lb(15));
    printf("%X\n",lb(5));
    printf("16-31:************************************\n");
    printf("%X\n",lw(16));
    printf("%X\n",lw(18));
    printf("%X\n",lw(23));
    printf("%X\n",lw(25));
    printf("%X\n",lh(20));
    printf("%X\n",lh(27));
    printf("%X\n",lh(30));
    printf("%X\n",lh(24));
    printf("%X\n",lh(19));
    printf("%X\n",lh(28));
    printf("%X\n",lb(26));
    printf("%X\n",lb(21));
    printf("%X\n",lb(17));
    
    printf("32+:****************************************\n");
    printf("%X\n",lw(32));
    printf("%X\n",lw(33));
    printf("%X\n",lw(34));
    printf("%X\n",lw(36));
    printf("%X\n",lh(38));
    printf("%X\n",lh(40));
    printf("%X\n",lh(32));
    printf("%X\n",lb(33));
    printf("%X\n",lb(34));
    pirntf("%X\n",lb(37));
    printf("%X\n",lb(42));
    printf("%X\n",lb(50));
    printf("%X\n",lb(35));
    
}