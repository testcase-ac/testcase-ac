#include <cstdio>
 
int main(){
    long long int a[100] = {1, 1, 1, 2, 2,};
    for(int u = 5; u < 100; u++){
        a[u] = a[u-1] + a[u-5];
    }
    int n;
    scanf("%d", &n);
    int temp;
    for(int i = 0; i < n; i++){
        scanf("%d", &temp);
        printf("%lld\n", a[temp-1]);
    }
}
