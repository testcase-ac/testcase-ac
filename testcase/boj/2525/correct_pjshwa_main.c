#include <stdio.h>
int main(void){int h,m,m_p;scanf("%d",&h);scanf("%d",&m);scanf("%d",&m_p);m+=m_p;while(m>=60){m-=60;h++;}printf("%d %d",h%24,m);return 0;}