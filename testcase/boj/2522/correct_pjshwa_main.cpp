#include <cstdio>

void print_stars(int x, int n){
    if(x>n) x = 2*n - x;
    for(int i = 0; i < n - x; i++){
        printf(" ");
    }
    for(int i = 0; i < x; i++){
        printf("*");
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= 2*n - 1; i++){
        print_stars(i,n);
    }
    
    return 0;
}