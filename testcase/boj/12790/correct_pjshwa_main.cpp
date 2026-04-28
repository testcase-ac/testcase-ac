#include <cstdio>

int main(){
    int n, temp, a[4];
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++){
            scanf("%d", &a[j]);
        }
        for(int j = 0; j < 2; j++){
            scanf("%d", &temp);
            a[j] += temp;
            if(a[j] <= 1) a[j] = 1;
        }
        scanf("%d", &temp);
        a[2] += temp;
        if(a[2] <= 0) a[2] = 0;
        scanf("%d", &temp);
        a[3] += temp;
        printf("%d", a[0] + 5 * a[1] + 2 * (a[2] + a[3]));
    }
    return 0;
}