#include <bits/stdc++.h>
using namespace std;
#define int long long
int lcnt[] = {6,2,5,5,4,5,6,3,7,5};
int dp[16][160][10], p10[19];
int f(int i, int j, int k) {
	if(i == 0) {
		return j == lcnt[k] ? 0 : -2;
	}
	int &ret = dp[i][j][k];
	if(ret != -1)
		return ret;
	for(int t=0; t<=9; t++) {
		int r = f(i-1, j-lcnt[k], t);
		if(r == -2)
			continue;
		ret = p10[i-1]*t+r;
		return ret;
	}
	ret = -2;
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	p10[0] = 1;
	for(int i=1; i<=18; i++) {
		p10[i] = p10[i-1]*10;
	}
	memset(dp, -1, sizeof dp);
	string s;
	cin >> s;
	int orig = stoll(s);
	int n = s.size(), acc = 0;
	for(int i=n-1, j=0;; i--, j++) {
		int last = i >= 0 ? s[i]-'0' : -1;
		if(i >= 0)
			acc += lcnt[last];
		for(int t=last+1; t<=9; t++) {
			int r = f(j-(i<0), acc, t);
			if(r != -2) {
				for(int p=i+1; p<n; p++)
					s[p] = '0';
				if(i < 0) {
					s = "1" + s;
					i += 2;
				}
				s[i] = t+'0';
				int casted = stoll(s);
				return !(cout << casted-orig+r);
			}
		}
	}
}
