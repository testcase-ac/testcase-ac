#include <cstdio>
#include <algorithm>
bool is_ninty(long long int a, long long int b, long long int c){
    return a*a + b*b == c*c;
}
int main(){
    int t;
    scanf("%d", &t);
    long long int a[3];
    char yes[] = "yes";
    char no[] = "no";
    for(int i = 0; i < t; i++){
        for(int j = 0; j < 3; j++){
            scanf("%lld", &a[j]);
        }
        std::sort(a, a+3);
        printf("Scenario #%d:\n%s\n\n", i + 1, is_ninty(a[0],a[1],a[2])?yes:no);
    }
}