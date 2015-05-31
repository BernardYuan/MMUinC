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
