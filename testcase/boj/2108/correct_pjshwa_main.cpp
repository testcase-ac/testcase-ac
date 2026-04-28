#include <bits/stdc++.h>

int main(){
    int n;
    scanf("%d", &n);
    int freq[8001] = {0};
    int a[n], sum = 0;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        sum += a[i];
        freq[a[i]+4000]++;
    }
    int max = 0;
    for(auto &x : freq){
        if(x > max) max = x;
    }
    int how_many = 0;
    int most_freq = 0;
    for(int i = 0; i < 8001; i++){
        if(freq[i] == max){
            how_many++;
            if(how_many <= 2) most_freq = i - 4000;
            else break;
        }
    }
    
    std::sort(a, a+n);
    int avg = round((double)sum / n);
    printf("%d\n%d\n%d\n%d", avg, a[(n-1)/2], most_freq ,a[n-1]-a[0]);
}
