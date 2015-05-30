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
