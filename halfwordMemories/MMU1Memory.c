#include <stdio.h>
typedef unsigned char byte;
typedef unsigned short halfword;
typedef unsigned int word;
halfword mem[256];

word lw(byte addr) {
	word data0, data1,data2;
	if(addr%2==0) {
		data0=mem[addr/2];
		data1=mem[addr/2+1];
		return (data0<<16)|data1;
	}
	else {
		data0=mem[addr/2];
		data1=mem[addr/2+1];
		data2=mem[addr/2+2];
		return (data0<<24)|(data1<<8)|(data2>>8);
	}
}

halfword lh(byte addr) {
	halfword data0, data1;
	
	if(addr%2==0) {
		return mem[addr/2];
	}
	else if(addr%2==1) {
		data0=mem[addr/2];
		data1=mem[addr/2+1];
		return (data0<<8)|(data1>>8);
	}
	
}

byte lb(byte addr) {
	byte data;
	if(addr%2==0) {
		data=mem[addr/2]>>8;
	}
	else if(addr%2==1) {
		data=mem[addr/2];
	}
	return data;
}

void sw(byte addr, word data) {
	if(addr%2==0) {
		mem[addr/2]=data>>16;
		mem[addr/2+1]=data;		
	}
	else if(addr%2==1) {
		mem[addr/2]&=0xff00;
		mem[addr/2]|=data>>24;
		mem[addr/2+1]=data>>8;
		mem[addr/2+2]&=0x00ff;
		mem[addr/2+2]|=(data&0x000000ff)<<8;
	}
}

void sh(byte addr, halfword data) {
	if(addr%2==0) {
		mem[addr/2]=data;
	}
	else if(addr%2==1) {
		mem[addr/2]&=0xff00;
		mem[addr/2]|=data>>8;
		mem[addr/2+1]&=0x00ff;
		mem[addr/2+1]|=data<<8;
	}
}

void sb(byte addr, byte data) {
	halfword data0=data;
	if(addr%2==0) {
		mem[addr/2]&=0x00ff;
		mem[addr/2]|=data0<<8;
	}
	else if(addr%2==1) {
		mem[addr/2]&=0xff00;
		mem[addr/2]|=data0;
	}
}