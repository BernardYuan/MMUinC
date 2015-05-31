#include<stdio.h>
typedef unsigned int word;
typedef unsigned short halfword;
typedef unsigned char byte;
byte Mem[256];
word lw(byte addr) {
    word data0,data1,data2,data3;
    
    data0=Mem[addr];
    data1=Mem[addr+1];
    data2=Mem[addr+2];
    data3=Mem[addr+3];
    
    return (data0<<24)|(data1<<16)|(data2<<8)|(data3);
}

halfword lh(byte addr) {
    halfword data0, data1;
    

    data0=Mem[addr];
    data1=Mem[addr+1];
    
    return (data0<<8)|(data1);
}

byte lb(byte addr) {
    byte data0;
    
    data0=Mem[addr];
    return data0;
}

void sw(byte addr,word data) {
    
    Mem[addr]=data>>24;
    Mem[addr+1]=data>>16&0x000000ff;
    Mem[addr+2]=data>>8&0x000000ff;
    Mem[addr+3]=data&0x000000ff;
}

void sh(byte addr,halfword data) {
    Mem[addr]=data>>8;
    Mem[addr+1]=data&0x00ff;

}
void sb(byte addr,byte data) {    
    Mem[addr]=data;
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
