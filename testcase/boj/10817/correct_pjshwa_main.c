#include <stdio.h>



int main(void){

    int a[3];
    int temp;
    
    for(int i = 0; i < 3; i++){
        scanf("%d", &a[i]);
    }
    
    if(a[0] > a[1]){
        temp = a[0];
        a[0] = a[1];
        a[1] = temp;
    }

    if(a[1] > a[2]){
        temp = a[1];
        a[1] = a[2];
        a[2] = temp;
    }

    if(a[0] > a[1]){
        temp = a[0];
        a[0] = a[1];
        a[1] = temp;
    }

    printf("%d", a[1]);

    return 0;
}