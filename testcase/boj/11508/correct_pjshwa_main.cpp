#include <cstdio>
#include <algorithm>

int main(){
    int n;
    scanf("%d", &n);
    
    long long int a[n];
    for(auto &x : a){
        scanf("%lld", &x);
    }
    std::sort(a, a+n, [](long long int x, long long int y){return x > y;});
    long long int sum = 0;
    for(int i = 0; i < n; i += 3){
        sum += a[i];
    }
    for(int i = 1; i < n; i += 3){
        sum += a[i];
    }
    printf("%lld", sum);
}