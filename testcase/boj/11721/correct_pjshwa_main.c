#include <stdio.h>

int main(void){
	char s[101];

	scanf("%s", s);

	int count = 0;

	char *char_ptr = s;

	while(*char_ptr){

		printf("%c", *char_ptr);
		count++;

		if(count == 10){
			printf("\n");
			count = 0;
		}
		char_ptr++;
	}	
}