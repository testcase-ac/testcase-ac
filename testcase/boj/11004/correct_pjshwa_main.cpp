#include <cstdio>
#include <algorithm>

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    int a[n];
    for(auto &x : a){
        scanf("%d", &x);
    }
    std::sort(a, a+n);
    printf("%d", a[k-1]);
}