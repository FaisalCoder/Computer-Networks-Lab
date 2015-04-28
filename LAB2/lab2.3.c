#include<stdio.h>
#include <string.h>
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
char hexToChar(int a){
	char hex_in_char;
	if(a == 0xa) hex_in_char = 'a';
	else if(a == 0xb) hex_in_char = 'b';
	else if(a == 0xc) hex_in_char = 'c';
	else if(a == 0xd) hex_in_char = 'd';
	else if(a == 0xe) hex_in_char = 'e';
	else if(a == 0xf) hex_in_char = 'f';
	else if(a == 0x0) hex_in_char = '0';
	else if(a == 0x1) hex_in_char = '1';
	else if(a == 0x2) hex_in_char = '2';
	else if(a == 0x3) hex_in_char = '3';
	else if(a == 0x4) hex_in_char = '4';
	else if(a == 0x5) hex_in_char = '5';
	else if(a == 0x6) hex_in_char = '6';
	else if(a == 0x7) hex_in_char = '7';
	else if(a == 0x8) hex_in_char = '8';
	else if(a == 0x9) hex_in_char = '9';
	return hex_in_char;
}
char* hexToBin(char a){
    char* bin;
    if(a == 'a') bin = "1010";
	else if(a == 'b') bin = "1011";
	else if(a == 'c') bin = "1100";
	else if(a == 'd') bin = "1101";
	else if(a == 'e') bin = "1110";
	else if(a == 'f') bin = "1111";
	else if(a == '0') bin = "0000";
	else if(a == '1') bin = "0001";
	else if(a == '2') bin = "0010";
	else if(a == '3') bin = "0011";
	else if(a == '4') bin = "0100";
	else if(a == '5') bin = "0101";
	else if(a == '6') bin = "0110";
	else if(a == '7') bin = "0111";
	else if(a == '8') bin = "1000";
	else if(a == '9') bin = "1001";
	return bin;
}
char binToHex(char* a){
    char hex;
	if(!strcmp(a, "1010")) hex = 'a';
	else if(!strcmp(a, "1011")) hex = 'b';
	else if(!strcmp(a, "1100")) hex = 'c';
	else if(!strcmp(a, "1101")) hex = 'd';
	else if(!strcmp(a, "1110")) hex = 'e';
	else if(!strcmp(a, "1111")) hex = 'f';
	else if(!strcmp(a, "0000")) hex = '0';
	else if(!strcmp(a, "0001")) hex = '1';
	else if(!strcmp(a, "0010")) hex = '2';
	else if(!strcmp(a, "0011")) hex = '3';
	else if(!strcmp(a, "0100")) hex = '4';
	else if(!strcmp(a, "0101")) hex = '5';
	else if(!strcmp(a, "0110")) hex = '6';
	else if(!strcmp(a, "0111")) hex = '7';
	else if(!strcmp(a, "1000")) hex = '8';
	else if(!strcmp(a, "1001")) hex = '9';
	return hex;
}
int main(){

	char IPHeader[] = "45000fb438e70000";    //first 16 half bytes

	printf("Input IPHeader %s\n",IPHeader);

	int headerLen = 0x4 * charToHex(IPHeader[1]);
	int totalLen = charToHex(IPHeader[4]) * 0x1000 + charToHex(IPHeader[5]) * 0x100 + charToHex(IPHeader[6]) * 0x10 + charToHex(IPHeader[7]);
	int messageLen = totalLen - headerLen;
	int MTU;            //MTU: Maximum size of frame payload

	printf("Enter the value of MTU (bytes) in hexadecimal : ");
	scanf("%x", &MTU);

	int noOfFrag = 0x1;
	char flag[5] = {'\0'};   // first 3 are flags hex to binary is minimum 4 bits and one bit for ending
	strcpy(flag,hexToBin(IPHeader[12]));

	if(MTU < messageLen && flag[1] != '1')
	{
		int maxAllowedBytesInFrag = (MTU/0x8) * 0x8;

		printf("maxAllowedBytesInFrag %x\n", maxAllowedBytesInFrag);

		int noOfFrag = messageLen/maxAllowedBytesInFrag + 0x1;
		char IPFragAll[noOfFrag*22];
		char IPHeaderFrag[20];
		strcpy(IPHeaderFrag, IPHeader);

		printf(" IPHeaderFrag %s\n", IPHeaderFrag);

		strcpy(IPFragAll," ");
		int fragFirstByte = 0x0;

		printf(" messageLen %x\n", messageLen);

		while(fragFirstByte < messageLen)
		{
			char flagsFrag[5] = {'\0'};   //flag of fragment
			flagsFrag[0] = flag[0];   //reserved
			flagsFrag[1] = flag[1];   //do not fragment if 1
			int fragLen;   //lenght of each fragment


            //checking if more fragments req.
			if((fragFirstByte + maxAllowedBytesInFrag) < messageLen)
			{
			    fragLen = maxAllowedBytesInFrag + headerLen;
			    flagsFrag[2] = '1'; //not last fragment
			}

			else
			{
			    fragLen = messageLen - fragFirstByte + headerLen;
			    flagsFrag[2] = '0';
			}

			//printf("%x\n", fragLen);
			//assigning fragment's total length  bytes

			IPHeaderFrag[4] = hexToChar(fragLen/0x1000);
			IPHeaderFrag[5] = hexToChar((fragLen%0x1000)/0x100);
			IPHeaderFrag[6] = hexToChar((fragLen%0x100)/0x10);
			IPHeaderFrag[7] = hexToChar(fragLen%0x10);

            int offset = fragFirstByte/0x8;

            printf("offset %x\n", offset);

            char* temp = hexToBin(hexToChar(offset/0x1000));   //storing first half byte of offset

            printf("temp %s\n", temp);

            flagsFrag[3] = temp[3];   //taking only the last bit of first half byte and storing in flag's one extra bit

            printf("flagsFrag %s\n", flagsFrag);

            //storing other offsets
            IPHeaderFrag[12] = binToHex(flagsFrag);
            IPHeaderFrag[13] = hexToChar((offset%0x1000)/0x100);
            IPHeaderFrag[14] = hexToChar((offset%0x100)/0x10);
            IPHeaderFrag[15] = hexToChar(offset%0x10);

            //adding fragments to main array
            strcat(IPFragAll, IPHeaderFrag);
            strcat(IPFragAll, " ");    //giving space between frags
			fragFirstByte += maxAllowedBytesInFrag;
		}
		printf("Fragments are :%s\n", IPFragAll);


		// ---------------------Defragmentation Model-------------------------------
		char IPHeaderFinal[20] = {'\0'};   //final IP result
		int temp1;
		int i = 1;
		for(temp1 = noOfFrag; temp1 > 0 ; temp1--)
		{
			char IPHeaderFrag[20] = {'\0'};     //will have individuAL fragment
			strncpy(IPHeaderFrag, IPFragAll + i, 16); // i = 1 because space in starting
			//fragment offset 13,14,15
			i += 17;
			if(IPHeaderFrag[13] == '0' && IPHeaderFrag[14] == '0'&& IPHeaderFrag[15] == '0' && temp1 == noOfFrag)
			{
				strcpy(IPHeaderFinal, IPHeaderFrag);
			}

			else if(temp1 == noOfFrag && IPHeaderFrag[13] != '0' && IPHeaderFrag[14] != '0'&& IPHeaderFrag[15] != '0')
			{
				printf("First Fragment Has an Offset Value not equal to Zero\n");  //error
			}

			else
			{
				int totalLenUpto = charToHex(IPHeaderFinal[4]) * 0x1000 + charToHex(IPHeaderFinal[5])*0x100+charToHex(IPHeaderFinal[6])*0x10+charToHex(IPHeaderFinal[7]) - headerLen;
                 //total data length except header length
				char flagCurrentFrag[4];   //flag of current frag
				strcpy(flagCurrentFrag,hexToBin(IPHeaderFrag[12]));   //copying

				int offsetCurrentFrag = charToHex(flagCurrentFrag[3])*0x1000+charToHex(IPHeaderFrag[13])*0x100+charToHex(IPHeaderFrag[14])*0x10+charToHex(IPHeaderFrag[15]);


				int totalLenCurrentFrag = charToHex(IPHeaderFrag[4]) * 0x1000 + charToHex(IPHeaderFrag[5])*0x100+charToHex(IPHeaderFrag[6])*0x10+charToHex(IPHeaderFrag[7]) - headerLen;

				if(totalLenUpto/0x8 == offsetCurrentFrag && totalLenUpto%0x8 == 0x0){
					totalLenUpto = totalLenUpto + headerLen + totalLenCurrentFrag;

					IPHeaderFinal[4] = hexToChar(totalLenUpto/0x1000);
					IPHeaderFinal[5] = hexToChar((totalLenUpto/0x100)%0x10);
					IPHeaderFinal[6] = hexToChar((totalLenUpto/0x10)%0x10);
					IPHeaderFinal[7] = hexToChar(totalLenUpto%0x10);
					if(flagCurrentFrag[2] == '0'){
						char flg[5]={'\0'};

						flg[0] = flagCurrentFrag[0];
						flg[1] = flagCurrentFrag[1];
						flg[2] = '0';
						flg[3] = '0';    //since original has only 0  offset
						IPHeaderFinal[12] = binToHex(flg);

						break;
					}
				}

				else
				{
					printf("Total length upto divided by 8 is not equal to the current value of offset\n ");
				}
			}


		}
		printf("IPHeaderFinal %s\n",IPHeaderFinal );
	}
	else
	{
		printf("%s\n No Fragmentation",IPHeader);
	}

	return 0;
}

