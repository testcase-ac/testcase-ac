#include <cstdio>

#define abs(x) x<0?-x:x
#define MOD_INT 1000000000

int fib(int n) {
	if (n == 0) return 0;
	else if (n == 1) return 1;
	else {
		int a = 0, b = 1;
		int c;
		for(int i = 0; i < n - 1; i++){
			c = (a + b) % MOD_INT;
			a = b; b = c;
		}
		return c;
	}
}

int main(){
	int n;
	scanf("%d", &n);

	if (n < 0 && n % 2 == 0) {
		printf("-1\n");
	}
	else if (n == 0) {
		printf("0\n0");
		return 0;
	}
	else {
		printf("1\n");	
	}

	printf("%d", fib(abs(n)));

}