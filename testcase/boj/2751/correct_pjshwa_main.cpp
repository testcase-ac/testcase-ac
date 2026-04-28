#include <cstdio>
#include <algorithm>
 
int main(){
    int t;
    scanf("%d", &t);
    int a[t];
    for(auto &x : a){
        scanf("%d", &x);
    }
    std::sort(a, a+t);
    for(auto &x : a){
        printf("%d\n", x);
    }
}