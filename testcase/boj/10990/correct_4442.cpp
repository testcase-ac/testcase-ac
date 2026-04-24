#include <stdio.h>
#define rep(i,n) for(int i=0;i<(n);i++)
using namespace std;
int main() {
	int n;
	scanf("%d", &n);
	rep(i, n) {
		rep(j, n-i-1) printf(" ");
		printf("*");
		if(i) {
			rep(j, 2*i-1) printf(" ");
			printf("*");
		}
		printf("\n");
	}
}
