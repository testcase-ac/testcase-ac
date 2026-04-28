#include<stdio.h>
main(){int n,m;scanf("%d%d",&n,&m);while(m--)putchar(m%(2*n)/2+'a');}