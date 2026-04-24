#include <bits/stdc++.h>
using namespace std;
char arr[105][105];
int dp[105][105];
int insq(int i, int j, int d, int pi, int pj, int pd) { // [l, r)
	int r = 0, c = 0;
	for(int t=i; t<i+d; t++) {
		if(pi <= t && t < pi+pd)
			r++;
	}
	for(int t=j; t<j+d; t++) {
		if(pj <= t && t < pj+pd)
			c++;
	}
	return d*d-r*c;
}
int main() {
	int R, C, mi, mj, mx = 0, m2i, m2j, mx2 = 0, mcnt = 0;
	cin >> R >> C;
	for(int i=1; i<=R; i++) {
		cin >> (arr[i]+1);
	}
	for(int i=R; i; i--) {
		for(int j=C; j; j--) {
			if(arr[i][j] != 'x') continue;
			dp[i][j] = min({dp[i+1][j], dp[i][j+1], dp[i+1][j+1]})+1;
			if(dp[i][j] > mx) {
				mx = dp[i][j];
				mi = i;
				mj = j;
			}
		}
	}
	for(int i=R; i; i--) {
		for(int j=C; j; j--) {
			if(arr[i][j] != 'x') continue;
			int t = insq(i, j, dp[i][j], mi, mj, mx);
			if(!t) continue;
			if(dp[i][j] > mx2) {
				mcnt = t;
				mx2 = dp[i][j];
				m2i = i;
				m2j = j;
			} else if(dp[i][j] == mx2) {
				if(t > mcnt) {
					mcnt = t;
					m2i = i;
					m2j = j;
				}
			}
		}
	}
	printf("%d %d %d\n", mi, mj, mx);
	if(!mx2)
		printf("%d %d %d\n", mi, mj, mx);
	else
		printf("%d %d %d\n", m2i, m2j, mx2);
}
