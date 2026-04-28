#include <cstdio>
int main(void){
    int n;
    scanf("%d", &n);
     
    int max_room = 1;
    int multiplier = 1;
    while(n > max_room){
        max_room += (6 * multiplier++);
    }
    
    printf("%d", multiplier);
    return 0;
}
