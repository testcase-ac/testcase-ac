#include <cstdio>

int main(){
	int n, m;
	while(true){
		scanf("%d%d", &n, &m);
		if(n == m && n == -1) break;
		long long possibilities = 1;
		for(int i = n + 1; i <= n + m; i++){
			possibilities *= i;
			possibilities /= (i-n);
		}
		if((long)n+m == possibilities){
			printf("%d+%d=%d\n", n, m, n+m);
		}
		else{
			printf("%d+%d!=%d\n", n, m, n+m);
		}
	}
}