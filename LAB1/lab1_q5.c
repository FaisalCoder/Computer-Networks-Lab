#include<stdio.h>
int charToHex(char a){
	int hex;
	if(a == 'a') hex = 0xa;
	else if(a == 'b') hex = 0xb;
	else if(a == 'c') hex = 0xc;
	else if(a == 'd') hex = 0xd;
	else if(a == 'e') hex = 0xe;
	else if(a == 'f') hex = 0xf;
	else if(a == '0') hex = 0x0;
	else if(a == '1') hex = 0x1;
	else if(a == '2') hex = 0x2;
	else if(a == '3') hex = 0x3;
	else if(a == '4') hex = 0x4;
	else if(a == '5') hex = 0x5;
	else if(a == '6') hex = 0x6;
	else if(a == '7') hex = 0x7;
	else if(a == '8') hex = 0x8;
	else if(a == '9') hex = 0x9;
	return hex;
}
int main(){
	//read from file;
	FILE *input;
	input = fopen("input.txt", "r");
	int sum = 0x0;
	char b ;
	while((b = fgetc(input)) != EOF  ){
		int a = 0x0;
		while(b != 0x20 && b != EOF){
			a = a*16 + charToHex(b);
			b = fgetc(input);
		}
		sum += a;
		if(sum/0xffff != 0x0){
			sum = (sum/0x10000) + (sum % 0x10000);
		}
	}
	printf("Checksum : %x\n", 0x10000-sum);
	if(sum == 0xffff ) printf("Checksum correct");
	else printf("Checksum incorrect");


	return 0;
}
