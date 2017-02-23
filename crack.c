#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
* this is going to be decidedly uneligant :/
*/

// prototyping
int check(char *cyc, char *hash, char *salt);

int main(int argc, string argv[]){
	if(argc != 2){
		printf("Usage: ./crack [hash]\n");
		return 1;
	}
	const int LLIM = (int) 'A';
	const int ULIM = (int) 'Z';
	
	char cyc[5] = {'A', 'A', 'A', 'A', '\0'};
	string hash = argv[1];
	char salt[3] = {(char) hash[0], (char) hash[1], '\0'};
	
	while(1){
		if(check(cyc, hash, salt) == 0){
			printf("%s\n", cyc);
			return 0;
		}
		for(int i = LLIM; i <= ULIM; i++){
			cyc[3] = (char) i;
			if(check(cyc, hash, salt) == 0){
				printf("%s\n", cyc);
				return 0;
			}
			cyc[3] = tolower((char) i);
			if(check(cyc, hash, salt) == 0){
				printf("%s\n", cyc);
				return 0;
			}
		}
		if((int) cyc[2] > (int) 'z'){
			cyc[2] = (char) LLIM;
			cyc[1] = (char) (1 + (int) cyc[1]);
			if(check(cyc, hash, salt) == 0){
				printf("%s\n", cyc);
				return 0;
			}
			if((int) cyc[1] > (int) 'z'){
				cyc[1] = (char) LLIM;
				cyc[0] = (char) (1 + (int) cyc[0]);
				if(check(cyc, hash, salt) == 0){
					printf("%s\n", cyc);
					return 0;
				}
				if((int) cyc[1] > (int) 'z'){
					return 1;
				}
			}
		}else{
			cyc[2] = (char) (1 + (int) cyc[2]);
			if(check(cyc, hash, salt) == 0){
				printf("%s\n", cyc);
				return 0;
			}
		}
		if((int) cyc[0] >= (int) 'z' && (int) cyc[1] >= 'z' && (int) cyc[2] >= (int) 'z' && (int) cyc[3] >= (int) 'z'){
			break;
		}
	}
	return 1;
}

int check(char *cyc, char *hash, char *salt){
	return strcmp(crypt(cyc, salt), hash); // it's either 0 or not
}
