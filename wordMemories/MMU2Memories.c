#include<stdio.h>
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
		data1=mem[(memchoose+1)%2][pos1]>>((4-left)*8);
	}
	return data0|data1;
}

halfword lh(byte addr) {   
	halfword data0=0, data1=0;
	byte left=addr%4;
	byte memchoose=(addr%8)/4;
	byte pos=addr/8;
	byte pos1=(addr%8==7)?pos+1:pos;
	
    data0=(left>2)?mem[memchoose][pos]<<8:mem[memchoose][pos]>>((2-left)*8);
    data1=(left>2)?mem[(memchoose+1)%2][pos1]>>24:0x00000000;
	
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
	
    mem[memchoose][pos]&=(left)? a<<((4-left)*8):0x00000000;
	mem[memchoose][pos]|=data>>(left*8);
	mem[(memchoose+1)%2][pos1]&=a>>(left*8);
    mem[(memchoose+1)%2][pos1]|=(left)?data<<((4-left)*8):0x00000000;
		
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
		mem[(memchoose+1)%2][pos1]&=0x00ffffff;
		mem[(memchoose+1)%2][pos1]|=data0<<24;
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
    
    for (int i=0; i<6; i++) {
        for (int j=0; j<=1; j++) {
            printf("%X\n",mem[j][i]);
        }
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