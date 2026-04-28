#include <stdio.h>

int main(void){
    char chess[8][8];
    
    for(int i = 0; i < 7; i++){
        scanf("%s\n", chess[i]);
    }
    scanf("%s", chess[7]);
    
    int whites = 0;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(chess[i][j] == 'F' && (j % 2) == (i % 2)) whites++;
        }
    }

    printf("%d", whites);
    return 0;
}