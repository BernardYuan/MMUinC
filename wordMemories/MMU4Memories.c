#inlcude<stdio.h>
typedef unsigned int word;
typedef unsigned short halfword;
typedef unsigned char byte;
word mem[4][256];

word lw(byte addr) {
	word data0=0, data1=0;
	byte left=addr%4;
	byte memchoose=(addr%16)/4;
	byte pos=addr/16;
	byte pos1=(addr%16>=13)?pos+1:pos;
		
	
	data0=mem[memchoose][pos]<<(left*8);
	if(left>0) {
		data1=mem[(memchoose+1)%4][pos1]>>((4-left)*8);
	}
	return data0|data1;
}

halfword lh(byte addr) {   //and elegant way to write it, but still need testing
	halfword data0=0, data1=0;
	byte left=addr%4;
	byte memchoose=(addr%16)/4;
	byte pos=addr/16;
	byte pos1=(addr%16==15)?pos+1:pos;
	
	data0=mem[memchoose][pos]>>((2-left)*8);
	data1=mem[(memchoose+1)%4][pos1]>>((6-left)*8);
	return data0|data1;
}
/*
byte lb(byte addr) {
	if(addr%16==0) {
	}
	else if(addr%16==1) {
	}
	else if(addr%16==2) {
	}
	else if(addr%16==3) {
	}
	else if(addr%16==4){
	}
	else if(addr%16==5){
	}
	else if(addr%16==6){
	}
	else if(addr%16==7){
	}
	else if(addr%16==8){
	}
	else if(addr%16==9){
	}
	else if(addr%16==10){
	}
	else if(addr%16==11){
	}
	else if(addr%16==12){
	}
	else if(addr%16==13){
	}
	else if(addr%16==14){
	}
	else if(addr%16==15){
	}
}*/
byte lb(byte addr) {
	byte left=addr%4;
	byte memchoose=(addr%16)/4;
	byte pos=addr/16;
	byte data;
	
	return data=mem[memchoose][pos]>>((3-left)*8);
}

void sw(byte addr, word data) {
	byte left = addr%4;
	byte memchoose = (addr%16)/4;
	byte pos = addr/16;
	byte pos1 = (addr%16>=13)?pos+1:pos;
	word a=0xffffffff;
	
	mem[memchoose][pos]&= a<<((4-left)*8);
	mem[memchoose][pos]|=data>>(left*8);

	mem[(memchoose+1)%4][pos1]&=a>>(left*8);
	mem[(memchoose+1)%4][pos1]|=data<<((4-left)*8);
		
}

void sh(byte addr, halfword data) {
	word data0=data;
	byte left=addr%4;
	byte memchoose = (addr%16)/4;
	byte pos=addr/16;
	byte pos1=(addr%16==15)?pos+1:pos;
	
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
	byte memchoose = (addr%16)/4;
	byte pos=addr/16;
		
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