#include <cstdio>
#include <algorithm>
int main(){
    int n;
    scanf("%d", &n);
    
    float numbers[n];
    for(auto &x : numbers){
        scanf("%f", &x);
    }
    std::sort(numbers, numbers+n);
    float max = numbers[n-1];
    float sum = 0.0;
    for(auto &x : numbers){
        x /= max;
        sum += x;
    }
    printf("%0.2f", sum * 100 / n);
}