#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
#include<random>
using namespace std;
using lld = long long int;
int pa[10009];
int p[10009];
int pl;
int a[10009];
void inil() {
	int i, j, k;
	for (i = 2; i <= 10000; i++) {
		if (pa[i] == 0) {
			pa[i] = pl;
			p[pl++] = i;
			for (j = i; j <= 10000 / i; j++) {
				pa[i * j] = 1;
			}
		}
	}
}
int n;
int b[10000];
int bl;
int main() {
	inil();
	int i, j, k, l;
	int t=1, tv = 0;
	while (t--) {
		scanf("%d", &n);
		for (i = 2; i <= n; i++) {
			k = i;
			for (j = 0; j < pl && p[j] <= k / p[j] && k>1; j++) {
				while (k % p[j] == 0) {
					a[j]++;
					k /= p[j];
				}
			}
			if (k > 1) {
				a[pa[k]]++;
			}
		}
		b[0] = 1;
		bl = 1;
		for (i = 0; i < pl; i++) {
			if (a[i] == 0)continue;
			for (j = 0; j < bl; j++) {
				b[j] *= (2 * a[i] + 1);
			}
			for (j = 0; j < bl; j++) {
				if (b[j] >= 10) {
					b[j + 1] += b[j] / 10;
					b[j] %= 10;
				}
			}
			for (;; j++) {
				if (b[j] >= 10) {
					b[j + 1] += b[j] / 10;
					b[j] %= 10;
					bl = j + 1;
				}
				else if (b[j] > 0) {
					bl = j + 1;
				}
				else
					break;
			}
			//res *= (2 * a[i] + 1);
		}
		for (i = bl - 1; i > 0; i--)if (b[i])break;
		for (; i >= 0; i--)printf("%d", b[i]);
		//printf("%lld\n", res);
	}
}
