#include <cstdio>

int main(){
    int n,m;
    scanf("%d%d", &n, &m);
    n+=24;
    m+=15;n--;
    if(m>=60){
        m-=60;
        n++;
    }
    n%=24;
    printf("%d %d", n, m);
}