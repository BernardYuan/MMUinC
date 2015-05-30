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