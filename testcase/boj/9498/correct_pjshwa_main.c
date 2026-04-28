#include <stdio.h>
 
int main(void){
    int score;
    scanf("%d", &score);
     
    score /= 10;
    char c='A';
    switch(score){
        case 10:
        case 9: break;
        case 8: c='B'; break;
        case 7: c='C'; break;
        case 6: c='D'; break;
        default: c='F';
    }
    printf("%c", c);
}