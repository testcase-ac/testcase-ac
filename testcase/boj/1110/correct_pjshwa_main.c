#include <stdio.h>

int main(void){
    
    int number;

    scanf("%d", &number);

    int cycles = 0;

    int original_number = number;
    int n_10, n_1;

    do{
        n_10 = number / 10;
        n_1 = number % 10;
        cycles++;
        number = 10 * n_1 + (n_1 + n_10) % 10;
    }while(original_number != number);

    printf("%d", cycles);

}