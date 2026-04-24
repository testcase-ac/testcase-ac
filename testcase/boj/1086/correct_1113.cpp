#include <bits/stdc++.h>
using namespace std;
#define int long long
int K, p10[5000];
struct num {
	string s;
	int mod, len;
	void calc() {
		len = s.size();
		mod = 0;
		int p = 1;
		for(int i=len-1; i>=0; i--) {
			mod += p*(s[i] - '0');
			p *= 10;
			p %= K;
			mod %= K;
		}
	}
};
int tomod(int t) {
	t %= K;
	if(t < 0)
		return t + K;
	return t;
}
num arr[15];
int dp[1<<15][100], n;
int f(int bm, int t) {
	if(!bm) {
		return t ? 0 : 1;
	}
	int &ret = dp[bm][t];
	if(ret != -1)
		return ret;
	ret = 0;
	int tlen = 0;
	for(int i=0; i<n; i++) {
		if(bm & (1 << i))
			tlen += arr[i].len;
	}
	for(int i=0; i<n; i++) {
		if(bm & (1 << i)) {
			tlen -= arr[i].len;
			ret += f(bm ^ (1 << i), tomod(t-p10[tlen]*arr[i].mod));
			tlen += arr[i].len;
		}
	}
	//printf("bm = %d, t = %d, ret = %d\n", bm, t, ret);
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	for(int i=0; i<n; i++)
		cin >> arr[i].s;
	cin >> K;
	p10[0] = 1;
	for(int i=1; i<5000; i++)
		p10[i] = (p10[i-1] * 10) % K;
	memset(dp, -1, sizeof dp);
	for(int i=0; i<n; i++)
		arr[i].calc();
	int x = f((1<<n)-1, 0), y = 1;
	for(int i=2; i<=n; i++)
		y *= i;
	int g = gcd(x, y);
	printf("%lld/%lld\n", x/g, y/g);
}
