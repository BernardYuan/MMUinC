#inlcude<stdio.h>
typedef unsigned int word;
typedef unsigned short halfword;
typedef unsigned char byte;
word mem[2][256];

word lw(byte addr) {
	word data0=0, data1=0;
	byte left=addr%4;
	byte memchoose=(addr%8)/4;
	byte pos=addr/8;
	byte pos1=(addr%8>=5)?pos+1:pos;
		
	data0=mem[memchoose][pos]<<(left*8);
	if(left>0) {
		data1=mem[(memchoose+1)%4][pos1]>>((4-left)*8);
	}
	return data0|data1;
}

halfword lh(byte addr) {   
	halfword data0=0, data1=0;
	byte left=addr%4;
	byte memchoose=(addr%8)/4;
	byte pos=addr/8;
	byte pos1=(addr%8==7)?pos+1:pos;
	
	data0=mem[memchoose][pos]>>((2-left)*8);
	data1=mem[(memchoose+1)%4][pos1]>>((6-left)*8);
	
	return data0|data1;
}

byte lb(byte addr) {
	byte left=addr%4;
	byte memchoose=(addr%8)/4;
	byte pos=addr/8;
	byte data;
	return data=mem[memchoose][pos]>>((3-left)*8);
}

void sw(byte addr, word data) {
	byte left = addr%4;
	byte memchoose = (addr%8)/4;
	byte pos = addr/8;
	byte pos1 = (addr%8>=5)?pos+1:pos;
	word a=0xffffffff;
	
	mem[memchoose][pos]&= a<<((4-left)*8);
	mem[memchoose][pos]|=data>>(left*8);
	mem[(memchoose+1)%4][pos1]&=a>>(left*8);
	mem[(memchoose+1)%4][pos1]|=data<<((4-left)*8);
		
}

void sh(byte addr, halfword data) {
	word data0=data;
	byte left=addr%4;
	byte memchoose = (addr%8)/4;
	byte pos=addr/8;
	byte pos1=(addr%8==7)?pos+1:pos;
	
	if(left==0) {
		mem[memchoose][pos]&=0x0000ffff;
		mem[memchoose][pos]|=data0<<16;
	}
	else if(left==1) {
		mem[memchoose][pos]&=0xff0000ff;
		mem[memchoose][pos]|=data0<<8;
	}
	else if(left==2) {
		mem[memchoose][pos]&=0xffff0000;
		mem[memchoose][pos]|=data0;
	}
	else if(left==3) {
		mem[memchoose][pos]&=0xffffff00;
		mem[memchoose][pos]|=data0>>8;
		mem[(memchoose+1)%4][pos1]&=0x00ffffff;
		mem[(memchoose+1)%4][pos1]|=data0<<24;
	}
}

void sb(byte addr, byte data) {
	word data0=data;
	byte left=addr%4;
	byte memchoose = (addr%8)/4;
	byte pos=addr/8;
		
	if(left==0) {
		mem[memchoose][pos]&=0x00ffffff;
		mem[memchoose][pos]|=data0<<24;
	}
	else if(left==1) {
		mem[memchoose][pos]&=0xff00ffff;
		mem[memchoose][pos]|=data0<<16;
	}
	else if(left==2) {
		mem[memchoose][pos]&=0xffff00ff;
		mem[memchoose][pos]|=data0<<8;
	}
	else if(left==3) {
		mem[memchoose][pos]&=0xffffff00;
		mem[memchoose][pos]|=data0;
	}
}