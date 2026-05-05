#include <stdio.h>

typedef long long ll;

int main(){
    int N;
    ll P[10], M;
    scanf("%d", &N);
    ll min = 2000000000000000000;
    for(int i = 0; i < 10; i++){
        if(i < N){
            scanf("%lld", &P[i]);
            if(i != 0 && min > P[i]){
                min = P[i];
            }
        }else{
            P[i] = -1;
        }
    }
    scanf("%lld", &M);
    if(M < min){
        if(M < P[0]){
            printf("0\n\n\n");
        }else{
            printf("1\n0\n0\n");
        }
        return 0;
    }
    ll digit, cost;
    if(min > P[0]){
        digit = 1+(M-min)/P[0];
        cost = M-digit*P[0];
        min = P[0];
    }else{
        digit = M/min;
        cost = M-digit*min;
    }
    printf("%lld\n", digit);
    ll count[10];
    for(int i = 9; i >= 0; i--){
        if(P[i] == -1){
            count[i] = 0;
        }else if(min == P[i]){
            count[i] = digit;
            for(int j = 0; j < i; j++){
                count[j] = 0;
            }
            break;
        }else{
            if(cost/(P[i]-min) > digit){
                count[i] = digit;
                digit = 0;
                for(int j = 0; j < i; j++){
                    count[j] = 0;
                }
                break;
            }else{
                count[i] = cost/(P[i]-min);
                digit -= cost/(P[i]-min);
                cost %= P[i]-min;
            }
        }
    }
    ll maxcount[10];
    ll mincount[10];
    ll counts = 50;
    for(int i = 9; i >= 0; i--){
        if(counts == 0){
            maxcount[i] = 0;
        }else if(counts >= count[i]){
            maxcount[i] = count[i];
            counts -= count[i];
        }else{
            maxcount[i] = counts;
            counts = 0;
        }
    }
    for(int i = 9; i >= 0; i--){
        for(int j = 0; j < maxcount[i]; j++){
            printf("%d", i);
        }
    }
    printf("\n");
    counts = 50;
    for(int i = 0; i < 10; i++){
        if(counts == 0){
            mincount[i] = 0;
        }else if(counts >= count[i]){
            mincount[i] = count[i];
            counts -= count[i];
        }else{
            mincount[i] = counts;
            counts = 0;
        }
    }
    for(int i = 9; i >= 0; i--){
        for(int j = 0; j < mincount[i]; j++){
            printf("%d", i);
        }
    }
    printf("\n");
}
