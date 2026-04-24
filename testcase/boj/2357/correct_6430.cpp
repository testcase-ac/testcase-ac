#include <stdio.h>
#include <algorithm>

using namespace std;

#define MOD 1000000007
#define rep(i, n) for(int i=0; i<(n); i++)
// Iterative segment tree implementation adapted for this solution.
// Reference: http://codeforces.com/blog/entry/18051
#define MAXN 100000
int mintree[2*MAXN], maxtree[2*MAXN];
int n, m;

int minquery(int l, int r) {
	int ret = 1000000007;
	l += n, r += n;
	while(l < r) {
		if(l % 2) {
			ret = min(ret, mintree[l]);
			l++;
		}
		if(r % 2) {
			r--;
			ret = min(ret, mintree[r]);
		}
		l /= 2, r /= 2;
	}
	return ret;
}
int maxquery(int l, int r) {
	int ret = 0;
	l += n, r += n;
	while(l < r) {
		if(l % 2) {
			ret = max(ret, maxtree[l]);
			l++;
		}
		if(r % 2) {
			r--;
			ret = max(ret, maxtree[r]);
		}
		l /= 2, r /= 2;
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i=n; i<2*n; i++) {
		int inp;
		scanf("%d", &inp);
		mintree[i] = maxtree[i] = inp;
	}
	for(int i=n-1;i>0;i--) {
		mintree[i] = min(mintree[2*i], mintree[2*i+1]);
		maxtree[i] = max(maxtree[2*i], maxtree[2*i+1]);
	}
	rep(i, m) {
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d %d\n", minquery(a-1,b), maxquery(a-1,b));
	}
}
