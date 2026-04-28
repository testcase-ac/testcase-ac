#include <cstdio>

int main(){
    int n;
    scanf("%d", &n);
    int answer = 0;
    switch(n){
        case 1: answer = -1; break;
        case 2: answer = -1; break;
        case 3: answer = 1; break;
        case 4: answer = -1; break;
        case 5: answer = 1; break;
        case 6: answer = 2; break;
        case 7: answer = -1; break;
        default:
            while(n % 5){
                n -= 3;
                answer++;
            }
            answer += (n/5);
    }
    printf("%d", answer);
}