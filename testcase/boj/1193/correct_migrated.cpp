#include <stdio.h>
int main(){
    int n=0;
    short int m=1;
    scanf("%d",&n);
    while(n>m)n-=m++;
    if(m%2==0){printf("%d/%d",n,m-n+1);}
    else{printf("%d/%d",m-n+1,n);}
}
