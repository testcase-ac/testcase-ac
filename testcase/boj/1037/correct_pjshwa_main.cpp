#include <cstdio>
#include <algorithm>
 
int main(){
    int numbers;
     
    scanf("%d", &numbers);
    long long int a[numbers];
    for(int i = 0; i < numbers; i++){
        scanf("%lld", &a[i]);
    }
    std::sort(a, a + numbers);
    printf("%lld", a[0]*a[numbers-1]);
}