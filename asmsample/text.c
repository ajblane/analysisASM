#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int asmi = 10;
    int asmj = 20;
   // asm("int3");
   /*
    __asm__("xorl %0,%1"
          : "=r"(asmi)
          : "0"(asmj)
	  : "memory"); 
   */
    /*
    int src = 1;
    int src2 = 2;
    int dst;
     asm ("mov %1, %0\n\t"
         "add $1, %0"
         : "=r" (dst)
         : "r" (src),"r"(src2));
    */
    unsigned int * dtr;
    asm volatile("sidt %0":"=m" (*dtr)); 
    return 0;
}
