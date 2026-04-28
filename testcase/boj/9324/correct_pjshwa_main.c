#include <stdio.h>
#include <string.h>

int main(void){

    int n;

    scanf("%d", &n);

    char message[100001];
    int freq[26] = {0};

    int string_length;
    

    for(int i = 0; i < n; i++){
        scanf("%s", message);

        int check = 0;
        for(int j = 0; j < 26; j++){
            freq[j] = 0;
        }
        string_length = strlen(message);

        for(int j = 0; j < string_length; j++){
            freq[message[j]-'A']++;
            if(freq[message[j]-'A'] == 3){
                if(message[j] != message[j+1]){
                    check = 1;
                    break;
                }
                freq[message[j++]-'A'] = 0;
            }
        }
        check?printf("FAKE"):printf("OK");
        printf("\n");
    }

    return 0;
}