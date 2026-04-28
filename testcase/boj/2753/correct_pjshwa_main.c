#include <stdio.h>

int main(void){
    int year;
    scanf("%d", &year);
    
    int lunar = 0;
    if(!(year % 4) && year % 100) lunar = 1;
    else if (!(year % 400)) lunar = 1;
    
    printf("%d", lunar);
    
    return 0;
}