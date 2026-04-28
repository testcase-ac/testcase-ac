#include <stdio.h>

int main(void){
	char s[101];

	scanf("%s", s);

	char *char_ptr = s;
	int strlen = 0;

	while(*char_ptr){

		strlen++;
		char_ptr++;
	}

	int palindrome = 1;

	for(int i = 0; i < strlen / 2; i++){
		if(s[i] != s[strlen - 1 - i]){
			palindrome = 0;
			break;
		}
	}

	printf("%d", palindrome);

}