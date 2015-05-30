#inlcude<stdio.h>
typedef unsigned int word;
typedef unsigned short halfword;
typedef unsigned char byte;
word mem[256];

word lw(byte addr) {
	word data0=0, data1=0;
	byte left=addr%4;
	byte pos=addr/4;
	byte pos1=(left)?pos+1:pos;
	
	data0=mem[pos]<<(left*8);
	if(left>0) {
		data1=mem[pos1]>>((4-left)*8);
	}
	return data0|data1;
}

halfword lh(byte addr) {   
	halfword data0=0, data1=0;
	byte left=addr%4;
	byte pos=addr/4;
	byte pos1=(left>2)?pos+1:pos;
	
	data0=mem[pos]>>((2-left)*8);
	data1=mem[pos1]>>((6-left)*8);
	
	return data0|data1;
}

byte lb(byte addr) {
	byte left=addr%4;
	byte pos=addr/4;
	byte data;
	return data=mem[pos]>>((3-left)*8);
}

void sw(byte addr, word data) {
	byte left = addr%4;
	byte pos = addr/4;
	byte pos1 = (left)?pos+1:pos;
	word a=0xffffffff;
	
	mem[pos]&= a<<((4-left)*8);
	mem[pos]|=data>>(left*8);
	mem[pos1]&=a>>(left*8);
	mem[pos1]|=data<<((4-left)*8);
		
}

void sh(byte addr, halfword data) {
	word data0=data;
	byte left=addr%4;
	byte pos=addr/4;
	byte pos1=(left==3)?pos+1:pos;
	
	if(left==0) {
		mem[pos]&=0x0000ffff;
		mem[pos]|=data0<<16;
	}
	else if(left==1) {
		mem[pos]&=0xff0000ff;
		mem[pos]|=data0<<8;
	}
	else if(left==2) {
		mem[pos]&=0xffff0000;
		mem[pos]|=data0;
	}
	else if(left==3) {
		mem[pos]&=0xffffff00;
		mem[pos]|=data0>>8;
		mem[pos1]&=0x00ffffff;
		mem[pos1]|=data0<<24;
	}
}

void sb(byte addr, byte data) {
	word data0=data;
	byte left=addr%4;
	byte pos=addr/4;
		
	if(left==0) {
		mem[pos]&=0x00ffffff;
		mem[pos]|=data0<<24;
	}
	else if(left==1) {
		mem[pos]&=0xff00ffff;
		mem[pos]|=data0<<16;
	}
	else if(left==2) {
		mem[pos]&=0xffff00ff;
		mem[pos]|=data0<<8;
	}
	else if(left==3) {
		mem[pos]&=0xffffff00;
		mem[pos]|=data0;
	}
}