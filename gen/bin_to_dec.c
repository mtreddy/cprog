/*
 * Program to convert bin to dec
 * gcc bin_to_dec.c  -g -o bin_to_dec
 */

#include<stdio.h>

int main(){
	char bstr[]  = "100";
	int dec = 0;
	printf("\n input binary num = %s \n", bstr);
	do{
		int pos = 0;
		for(int ind = sizeof(bstr) - 2; ind >= 0; ind--) {
			if(bstr[ind] == '1') {
				dec = dec + 1 << pos;
				pos = pos+1;		
			} else if (bstr[ind] == '0') {
				pos = pos+1;		
			} else {
				printf("Invalid bit pattern found\n");	
				break;
			}
		}
	}while(0);
	printf("dec value for string %s is %d\n", bstr, dec);
}
