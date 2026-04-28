#include <cstdio>

int PowerOf10(int power){
    int result = 1;
    for(int i = 0; i < power; i++){
        result = (result << 3) + (result << 1);
    }
    return result;
}

int main(){
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        int temp;
        scanf("%d", &temp);
        int answer = temp;
        int index = 1;
        while(temp >= 10){
            if(temp % 10 >= 5){
                answer += PowerOf10(index);
                temp += 10;
            }
            answer -= answer % PowerOf10(index);
            temp /= 10;
            index++;
        }
        printf("%d\n", answer);
    }
}