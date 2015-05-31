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

/*int main(void) {
	sw(0,0x01234567);
	sh(4,0x89ab);
	sb(6,0xcd);
	sw(7,0xeffedcba);
	sh(11,0x9876);
	sb(13,0x54);
	
	printf("%X\n", lw(2));
	printf("%X\n", lw(7));
	
	printf("%X\n", lh(8));
	printf("%X\n", lh(3));
	
	printf("%X\n", lb(0));
	printf("%X\n", lb(11));
}*/

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
    for (int i=0; i<=40; i+=2) {
        printf("%04X%04X\n",mem[i],mem[i+1]);
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