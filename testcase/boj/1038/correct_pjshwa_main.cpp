#include <cstdio>

int main(){
    int n;
    scanf("%d", &n);
    if(n > 1022){
        printf("-1");
        return 0;
    }
    int i_base[10], i_dec[10];
    for(int i = 0; i < 10; i++){
        i_base[i] = 9-i;
        i_dec[i] = -1;
    }
    i_dec[9] = 0;
    for(int i = 0; i < n; i++){
        i_dec[9]++;
        for(int i = 9; i > 0; i--){
            if(i_dec[i-1] == -1){
                if(i_dec[i] == 10){
                    i_dec[i] = i_base[i];
                    i_dec[i-1] = i_base[i-1];
                }
            } 
            else{
                if(i_dec[i] == i_dec[i-1]){
                    i_dec[i] = i_base[i];
                    i_dec[i-1]++;
                }
            }
        }
    }
    for(int i = 0; i < 10; i++){
        if(i_dec[i] != -1) printf("%d", i_dec[i]);
    }
    return 0;
}