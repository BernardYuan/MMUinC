#include <stdio.h>
typedef unsigned char byte;
typedef unsigned short halfword;
typedef unsigned int word;
halfword mem0[256];
halfword mem1[256];

word lw(byte addr) {
	word data0, data1, data2;
	if(addr%4==0) {
		data0=mem0[addr/4];
		data1=mem1[addr/4];
		return (data0<<16)|data1;	
	}
	else if(addr%4==1) {
		data0=mem0[addr/4]&0x000000ff;
		data1=mem1[addr/4];
		data2=mem0[addr/4+1]&0x0000ff00;;
		return (data0<<24)|(data1<<8)|(data2>>8);
	}
	else if(addr%4==2) {
		data0=mem1[addr/4];
		data1=mem0[addr/4+1];
		return (data0<<16)|(data1);
	}
	else {
		data0=mem1[addr/4];
		data1=mem0[addr/4+1];
		data2=mem1[addr/4+1]&0x0000ff00;
		return (data0<<24)|(data1<<8)|(data2>>8);
	}
}

halfword lh(byte addr) {
	halfword data0, data1;
	
	if(addr%4==0) {
		return mem0[addr/4];
	}
	else if(addr%4==1) {
		data0=mem0[addr/4];
		data1=mem1[addr/4];
		return (data0<<8)|(data1>>8);
	}
	else if(addr%4==2) {
		return mem1[addr/4];
	}
	else {
		data0=mem1[addr/4];
		data1=mem0[addr/4+1];
		return (data0<<8)|(data1>>8);
	}
}

byte lb(byte addr) {
	byte data;
	if(addr%4==0) {
		data=mem0[addr/4]>>8;
	}
	else if(addr%4==1) {
		data=mem0[addr/4];
	}
	else if(addr%4==2) {
		data=mem1[addr/4]>>8;
	}
	else {
		data=mem1[addr/4];
	}
	return data;
}

void sw(byte addr, word data) {
	if(addr%4==0){
		mem0[addr/4]=data>>16;
		mem1[addr/4]=data;
	}
	else if(addr%4==1) {
		mem0[addr/4]&=0xff00;
		mem0[addr/4]|=data>>24;
		mem1[addr/4]=data>>8;
		mem0[addr/4+1]&=0x00ff;
		mem0[addr/4+1]|=(data<<8)&0x0000ff00;
	}
	else if(addr%4==2) {
		mem1[addr/4]=data>>16;
		mem0[addr/4+1]=data;
	}
	else {
		mem1[addr/4]&=0xff00;
		mem1[addr/4]|=data>>24;
		mem0[addr/4+1]=data>>8;
		mem1[addr/4+1]&=0x00ff;
		mem1[addr/4+1]|=(data<<8)&0x0000ff00;
	}
}

void sh(byte addr, halfword data) {
	if(addr%4==0){
		mem0[addr/4]=data;
	}
	else if(addr%4==1) {
		mem0[addr/4]&=0xff00;
		mem0[addr/4]|=data>>8;
		mem1[addr/4]&=0x00ff;
		mem1[addr/4]|=data<<8;
	}
	else if(addr%4==2) {
		mem1[addr/4]=data;
	}
	else {
		mem1[addr/4]&=0xff00;
		mem1[addr/4]|=data>>8;
		mem0[addr/4+1]&=0x00ff;
		mem0[addr/4+1]|=data<<8;
	}
}

void sb(byte addr, byte data) {
	halfword data0=data;
	if(addr%4==0){
		mem0[addr/4]&=0x00ff;
		mem0[addr/4]|=data0<<8;
	}
	else if(addr%4==1) {
		mem0[addr/4]&=0xff00;
		mem0[addr/4]|=data0;
	}
	else if(addr%4==2) {
		mem1[addr/4]&=0x00ff;
		mem1[addr/4]|=data0<<8;
	}
	else {
		mem1[addr/4]&=0xff00;
		mem1[addr/4]|=data0;
	}
}
int main(void) {
    sw(0,0x01234567);
    sw(3,0x89abcdef);
    sw(5,0xfedcba98);
    sw(6,0x76543210);
    sw(7,0x01234567);
    sw(14,0x89abcdef);
    
    
    sh(16,0xfedc);
    sh(21,0xba98);
    sh(26,0x7654);
    sh(27,0x3210);
    sh(31,0x0123);
    
    sb(33,0x45);
    sb(34,0x67);
    sb(35,0x89);
    sb(35,0xab);
    sb(34,0xcd);
    for (int i=0; i<=10; i++) {
        printf("%04X%04X\n",mem0[i],mem1[i]);
    }
    printf("0-15:*************************************\n");
    printf("%X\n",lw(0));
    printf("%X\n",lw(3));
    printf("%X\n",lw(6));
    printf("%X\n",lw(7));
    printf("%X\n",lw(9));
    printf("%X\n",lw(14));
    printf("%X\n",lh(8));
    printf("%X\n",lh(11));
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
    printf("%X\n",lb(37));
    printf("%X\n",lb(42));
    printf("%X\n",lb(50));
    printf("%X\n",lb(35));
    
}

