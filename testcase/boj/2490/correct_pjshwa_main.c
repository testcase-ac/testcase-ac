#include <stdio.h>

int main(void){
    int a[4], sum;
    for(int i = 0; i < 3; i++){
        sum = 0;
        for(int j = 0; j < 4; j++){
            scanf("%d", &a[j]);
            sum += a[j];
        }
        if(sum == 4) printf("E\n");
        else printf("%c\n", (char)(68-sum));
    }
    
    return 0;
}