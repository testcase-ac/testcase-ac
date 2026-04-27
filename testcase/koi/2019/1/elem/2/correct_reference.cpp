#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char p[101000], q[101000];
int n;
int main() {
	int i, TC;
	scanf("%d", &TC);
	while (TC--) {
		scanf("%s", p);
		n = strlen(p);
		for (i = 0; i < n; i++) {
			if (p[i] != p[n - 1 - i])break;
		}
		if (i == n) {
			puts("0");
			continue;
		}
		int pv = i, c = 0;
		for (i = 0; i < n; i++)if (i != pv)q[c++] = p[i];
		for (i = 0; i < c; i++)if (q[i] != q[c - 1 - i])break;
		if (i == c) {
			puts("1");
			continue;
		}
		c = 0;
		for (i = 0; i < n; i++)if (i != n-1-pv)q[c++] = p[i];
		for (i = 0; i < c; i++)if (q[i] != q[c - 1 - i])break;
		if (i == c) {
			puts("1");
			continue;
		}
		puts("2");
	}
	return 0;
}