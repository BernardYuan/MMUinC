#Lou Sir's real homework of Week11
#### The Single Clock CPU is actually for Week12
#### 袁博伟 Bernard Yuan
###Finished Parts
* Small Endians for word memory, halfword memory and byte memory. including the Multi-Memory situation.
* The instructions that are finished are:
  * lw, lh, lb, sw, sh, sb

### Parts to be done:
* Big Endians for what mentioned above.

* Debug those parts.

###Note
* The byte and halfword memories are relatively stable. While for the word bytes, some inductions are used to simplify the code, which makes the code more brief, while is not debugged yet.

###Testing
* The testing program are given with each .C file, in the main program
  * byte Memories:
    * 1 memory: passed
    * 2 memory: passed
    * 4 memory: passed
  * halfword Memories:
    * 1 memory: passed
    * 2 memory: passed
    * 4 memory: passed
* The testing program is following: which tests with nearly all cases except for overflow, or segment fault.


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
