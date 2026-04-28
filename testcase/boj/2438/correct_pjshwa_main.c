#include <stdio.h>

int main(void){
    
    int number;
    
    scanf("%d", &number);
    
    for(int i = 0; i < number; i++){
        for(int j = 0; j < i +1; j++){
            printf("*");
        }
        
        printf("\n");
    }
    return 0;
}