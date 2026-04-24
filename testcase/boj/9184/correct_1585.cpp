#include <bits/stdc++.h>
using namespace std;

int dp[21][21][21];
int w(int a, int b, int c) {
	if(a <= 0 || b <= 0 || c <= 0) {
		return 1;
	} else if(a > 20 || b > 20 || c > 20) {
		return w(20,20,20);
	} else if(dp[a][b][c]) {
		return dp[a][b][c];
	} else {
		int ret;
		if(a < b && b < c)
			ret = w(a,b,c-1) + w(a,b-1,c-1) - w(a,b-1,c);
		else
			ret = w(a-1,b,c) + w(a-1,b-1,c) + w(a-1,b,c-1) - w(a-1,b-1,c-1);
		dp[a][b][c] = ret;
		return ret;
	}
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int a, b, c;
	while(1) {
		cin >> a >> b >> c;
		if(a == -1 && b == -1 && c == -1) return 0;
		printf("w(%d, %d, %d) = %d\n", a, b, c, w(a,b,c));
	}
}
