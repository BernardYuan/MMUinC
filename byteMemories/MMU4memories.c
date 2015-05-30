#include<stdio.h>
typedef unsigned char byte;
typedef unsigned short halfword;
typedef unsigned int word;
byte Mem0[256];
byte Mem1[256];
byte Mem2[256];
byte Mem3[256];


word lw(byte addr) {
    word data0,data1,data2,data3;
    byte pos0, pos1 , pos2, pos3;

    pos0=(addr+3)/4;
    pos1=(addr+2)/4;
    pos2=(addr+1)/4;
    pos3=addr/4;

    if(addr%4==0){
        data0=Mem0[pos0];
        data1=Mem1[pos1];
        data2=Mem2[pos2];
        data3=Mem3[pos3];
    }
    else if(addr%4==1) {
        data0=Mem1[pos1];
        data1=Mem2[pos2];
        data2=Mem3[pos3];
        data3=Mem0[pos0];
    }
    else if(addr%4==2) {
        data0=Mem2[pos2];
        data1=Mem3[pos3];
        data2=Mem0[pos0];
        data3=Mem1[pos1];
    }
    else if(addr%4==3) {
        data0=Mem3[pos3];
        data1=Mem0[pos0];
        data2=Mem1[pos1];
        data3=Mem2[pos2];
    }
    return (data0<<24)|(data1<<16)|(data2<<8)|(data3);
}

halfword lh(byte addr) {
    byte pos0, pos1, pos2, pos3;
    halfword data0, data1;
    pos0=(addr+3)/4;
    pos1=(addr+2)/4;
    pos2=(addr+1)/4;
    pos3=addr/4;

    if(addr%4==0){
        data0=Mem0[pos0];
        data1=Mem1[pos1];
    }
    else if(addr%4==1){
        data0=Mem1[pos1];
        data1=Mem2[pos2];
    }
    else if(addr%4==2) {
        data0=Mem2[pos2];
        data1=Mem3[pos3];
    }
    else if(addr%4==3) {
        data0=Mem3[pos3];
        data1=Mem0[pos0];
    }
    return (data0<<8)|(data1);
}

byte lb(byte addr) {
    byte data0;
    byte pos0, pos1, pos2, pos3;
    pos0=(addr+3)/4;
    pos1=(addr+2)/4;
    pos2=(addr+1)/4;
    pos3=addr/4;

    if(addr%4==0) {
        data0=Mem0[pos0];
    }
    else if(addr%4==1) {
        data0=Mem1[pos1];
    }
    else if(addr%4==2) {
        data0=Mem2[pos2];
    }
    else if(addr%4==3) {
        data0=Mem3[pos3];
    }
    return data0;
}

void sw(byte addr,word data) {
    byte pos0, pos1, pos2, pos3;
    pos0=(addr+3)/4;
    pos1=(addr+2)/4;
    pos2=(addr+1)/4;
    pos3=addr/4;

    if (addr%4==0) {
        Mem0[pos0]=data>>24;
        Mem1[pos1]=data>>16&0x000000ff;
        Mem2[pos2]=data>>8&0x000000ff;
        Mem3[pos3]=data&0x000000ff;
    }
    else if(addr%4==1) {
        Mem1[pos1]=data>>24;
        Mem2[pos2]=data>>16&0x000000FF;
        Mem3[pos3]=data>>8&0x000000ff;
        Mem0[pos0]=data&0x000000ff;
    }
    else if (addr%4==2) {
        Mem2[pos2]=data>>24;
        Mem3[pos3]=data>>16&0x000000ff;
        Mem0[pos0]=data>>8&0x000000ff;
        Mem1[pos1]=data&0x000000ff;
    }
    else if(addr%4==3) {
        Mem3[pos3]=data>>24;
        Mem0[pos0]=data>>16&0x000000ff;
        Mem1[pos1]=data>>8&0x000000ff;
        Mem2[pos2]=data&0x000000ff;
    }
}
void sh(byte addr,halfword data) {
    byte pos0, pos1, pos2, pos3;
    pos0=(addr+3)/4;
    pos1=(addr+2)/4;
    pos2=(addr+1)/4;
    pos3=addr/4;

    if(addr%4==0){
        Mem0[pos0]=data>>8;
        Mem1[pos1]=data&0x00ff;
    }
    else if(addr%4==1){
        Mem1[pos1]=data>>8;
        Mem2[pos2]=data&0x00ff;
    }
    else if(addr%4==2) {
        Mem2[pos2]=data>>8;
        Mem3[pos3]=data&0x00ff;
    }
    else if(addr%4==3) {
        Mem3[pos3]=data>>8;
        Mem0[pos0]=data&0x00ff;
    }

}
void sb(byte addr,byte data) {
    byte pos0, pos1, pos2, pos3;
    pos0=(addr+3)/4;
    pos1=(addr+2)/4;
    pos2=(addr+1)/4;
    pos3=addr/4;

    if(addr%4==0) {
        Mem0[pos0]=data;
    }
    else if(addr%4==1) {
        Mem1[pos1]=data;
    }
    else if(addr%4==2) {
        Mem2[pos2]=data;
    }
    else if(addr%4==3) {
        Mem3[pos3]=data;
    }
}
int main(void) {
    word a=0x1234abcd;
    halfword b=0x12ab;
    byte c=0x1a;

    sw(0,a);
    sh(4,b);
    sb(6,c);

    printf("%x\n",lw(2));
    printf("%x\n",lh(6));
    printf("%x\n",lb(4));
}
