#include <stdio.h>


int main(void){

    int n, a, b;
    
    scanf("%d", &n);

    long long int bridges[30][30] = {0};

    for(long long int i = 0; i < 30; i++){
        bridges[0][i] = i + 1LL;
    }

    for(int i = 1; i < 30; i++){
        for(int j = i; j < 30; j++){
            for(int k = i - 1; k < j; k++){
                bridges[i][j] += bridges[i-1][k];
            }
        }
    }

    for(int i = 0; i < n; i++){
        scanf("%d", &a);
        scanf("%d", &b);
        printf("%lld\n", bridges[a-1][b-1]);
    }

    return 0;
}