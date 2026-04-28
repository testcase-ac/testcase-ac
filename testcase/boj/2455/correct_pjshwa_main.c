#include <stdio.h>
 
int main(void){
    int down, up;
    int passenger = 0;
    int max_passenger = 0;
     
    for(int i = 0; i < 4; i++){
        scanf("%d %d", &down, &up);
        passenger = passenger - down + up;
        if(passenger > max_passenger) max_passenger = passenger;
    }
     
    printf("%d", max_passenger);
}