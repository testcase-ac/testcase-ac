#include <stdio.h>

int main(){
	int n, k; scanf("%d %d",&n,&k);
	n -= k * (k + 1) / 2;
	if(n < 0) puts("-1");
	else printf("%d\n", k - 1 + (n % k != 0));
}
