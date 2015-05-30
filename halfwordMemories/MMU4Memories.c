#include<stdio.h>
typedef unsigned char byte;
typedef unsigned short halfword;
typedef unsigned int word;
halfword mem0[256];
halfword mem1[256];
halfword mem2[256];
halfword mem3[256];

word lw(byte addr) {
	word data0, data1, data2;
	if(addr%8==0) {
		data0=mem0[addr/8];
		data1=mem1[addr/8];
		return (data0<<16)|data1;	
	}
	else if(addr%8==1) {
		data0=mem0[addr/8]&0x00ff;
		data1=mem1[addr/8];
		data2=mem2[addr/8]&0xff00;
		return (data0<<24)|(data1<<8)|(data2>>8);
	}
	else if(addr%8==2) {
		data0=mem1[addr/8];
		data1=mem2[addr/8];
		return (data0<<16)|data1;
	}
	else if(addr%8==3) {
		data0=mem1[addr/8]&0x00ff;
		data1=mem2[addr/8];
		data2=mem3[addr/8]&0xff00;
		return (data0<<24)|(data1<<8)|(data2>>8);
	}
	else if(addr%8==4) {
		data0=mem2[addr/8];
		data1=mem3[addr/8];
		return (data0<<16)|data1;
	}
	else if(addr%8==5) {
		data0=mem2[addr/8]&0x00ff;
		data1=mem3[addr/8];
		data2=mem0[addr/8+1]&0xff00;
		return (data0<<24)|(data1<<8)|(data2>>8);
	}
	else if(addr%8==6) {
		data0=mem3[addr/8];
		data1=mem0[addr/8+1];
		return (data0<<16)|data1;
	}
	else if(addr%8==7) {
		data0=mem3[addr/8]&0x00ff;
		data1=mem0[addr/8];
		data2=mem1[addr/8]&0xff00;
		return (data0<<24)|(data1<<8)|(data2>>8);
	}
}

halfword lh(byte addr) {
	halfword data0, data1;
	
	if(addr%8==0) {
		return mem0[addr/8];
	}
	else if(addr%8==1) {
		data0=mem0[addr/8];
		data1=mem1[addr/8];
		return (data0<<8)|(data1>>8);
	}
	else if(addr%8==2) {
		return mem1[addr/8];
	}
	else if(addr%8==3) {
		data0=mem1[addr/8];
		data1=mem2[addr/8];
		return (data0<<8)|(data1>>8);	
	}
	else if(addr%8==4) {
		return mem2[addr/8];
	}
	else if(addr%8==5) {
		data0=mem2[addr/8];
		data1=mem3[addr/8];
		return (data0<<8)|(data1>>8);	
	}
	else if(addr%8==6) {
		return mem3[addr/8];
	}
	else if(addr%8==7) {
		data0=mem3[addr/8];
		data1=mem0[addr/8+1];
		return (data0<<8)|(data1>>8);	
	}
}

byte lb(byte addr) {
	byte data;
	if(addr%8==0) {
		return mem0[addr/8]>>8;
	}
	else if(addr%8==1) {
		data=mem0[addr/8];
	}
	else if(addr%8==2) {
		return mem1[addr/8]>>8;
	}
	else if(addr%8==3) {
		data=mem1[addr/8];
	}
	else if(addr%8==4) {
		return mem2[addr/8]>>8;
	}
	else if(addr%8==5) {
		data=mem2[addr/8];
	}
	else if(addr%8==6) {
		return mem3[addr/8]>>8;
	}
	else if(addr%8==7) {
		data=mem3[addr/8];
	}
	return data;
}

void sw(byte addr, word data) {
	if(addr%8==0) {
		mem0[addr/8]=data>>16;
		mem1[addr/8]=data;
	}
	else if(addr%8==1) {
		mem0[addr/8]&=0xff00;
		mem0[addr/8]|=data>>24;
		mem1[addr/8]=data>>8;
		mem2[addr/8]&=0x00ff;
		mem2[addr/8]|=(data<<8)&0x0000ff00;
	}
	else if(addr%8==2) {
		mem1[addr/8]=data>>16;
		mem2[addr/8]=data;		
	}
	else if(addr%8==3) {
		mem1[addr/8]&=0xff00;
		mem1[addr/8]|=data>>24;
		mem2[addr/8]=data>>8;
		mem3[addr/8]&=0x00ff;
		mem3[addr/8]|=(data<<8)&0x0000ff00;	
	}
	else if(addr%8==4) {
		mem2[addr/8]=data>>16;
		mem3[addr/8]=data;
	}
	else if(addr%8==5) {
		mem2[addr/8]&=0xff00;
		mem2[addr/8]|=data>>24;
		mem3[addr/8]=data>>8;
		mem0[addr/8+1]&=0x00ff;
		mem0[addr/8+1]|=(data<<8)&0x0000ff00;	
	}
	else if(addr%8==6) {
		mem3[addr/8]=data>>16;
		mem0[addr/8+1]=data;
	}
	else if(addr%8==7) {
		mem3[addr/8]&=0xff00;
		mem3[addr/8]|=data>>24;
		mem0[addr/8+1]=data>>8;
		mem1[addr/8+1]&=0x00ff;
		mem1[addr/8+1]|=(data<<8)&0x0000ff00;	
	}
}

void sh(byte addr, halfword data) {
	if(addr%8==0) {
		mem0[addr/8]=data;
	}
	else if(addr%8==1) {
		mem0[addr/8]&=0xff00;
		mem0[addr/8]|=data>>8;
		mem1[addr/8]&=0x00ff;
		mem1[addr/8]|=data<<8;
	}
	else if(addr%8==2) {
		mem1[addr/8]=data;
	}
	else if(addr%8==3) {
		mem1[addr/8]&=0xff00;
		mem1[addr/8]|=data>>8;
		mem2[addr/8]&=0x00ff;
		mem2[addr/8]|=data<<8;	
	}
	else if(addr%8==4) {
		mem2[addr/8]=data;
	}
	else if(addr%8==5) {
		mem2[addr/8]&=0xff00;
		mem2[addr/8]|=data>>8;
		mem3[addr/8]&=0x00ff;
		mem3[addr/8]|=data<<8;	
	}
	else if(addr%8==6) {
		mem3[addr/8]=data;
	}
	else if(addr%8==7) {
		mem3[addr/8]&=0xff00;
		mem3[addr/8]|=data>>8;
		mem0[addr/8+1]&=0x00ff;
		mem0[addr/8+1]|=data<<8;	
	}
}

void sb(byte addr, byte data) {
	halfword data0=data;
	if(addr%8==0) {
		mem0[addr/8]&=0x00ff;
		mem0[addr/8]|=data0<<8;
	}
	else if(addr%8==1) {
		mem0[addr/8]&=0xff00;
		mem0[addr/8]|=data0;
	}
	else if(addr%8==2) {
		mem1[addr/8]&=0x00ff;
		mem1[addr/8]|=data0<<8;		
	}
	else if(addr%8==3) {
		mem1[addr/8]&=0xff00;
		mem1[addr/8]|=data0;	
	}
	else if(addr%8==4) {
		mem2[addr/8]&=0x00ff;
		mem2[addr/8]|=data0<<8;	
	}
	else if(addr%8==5) {
		mem2[addr/8]&=0xff00;
		mem2[addr/8]|=data0;
	}
	else if(addr%8==6) {
		mem3[addr/8]&=0x00ff;
		mem3[addr/8]|=data0<<8;	
	}
	else if(addr%8==7) {
		mem3[addr/8]&=0xff00;
		mem3[addr/8]|=data0;
	}
}