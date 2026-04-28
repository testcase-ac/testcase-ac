#include <cstdio>
using namespace std;
 
int main(){
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1 - i; j++){
            printf(" ");
        }
        for(int j = 0; j < 2 * i + 1; j++){
            printf("*");
        }
        for(int j = 0; j < n - 1 - i; j++){
            printf(" ");
        }
        printf("\n");
    }

    return 0;
}