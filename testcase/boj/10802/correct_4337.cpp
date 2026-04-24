#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+3, MOD = 20150523;
int dp[MX][3][2][10];
inline int is_369(int i) {
	return i == 3 || i == 6 || i == 9;
}
bool do_last = true;
int f(string& s, int i, int cj, int ck) {
	if(i < 0) return 0;
	int ret = 0, a = s[i]-'0';
	for(int t=0; t<a; t++) {
		for(int j=0; j<3; j++) {
			for(int k=0; k<2; k++) {
				if((j+cj)%3 == 0 || k || ck) {
					//printf("at i=%lld, added at dp %lld, %lld, %lld, %lld. value is %lld\n", i, i+1, j, k, t, dp[i+1][j][k][t]);
					ret += dp[i+1][j][k][t];
				}
			}
		}
	}
	if(!i && do_last) { // add up last number
		ret += ((a+cj) % 3 == 0) || ck || is_369(a);
	}
	return (ret + f(s, i-1, (cj+a)%3,  ck || is_369(a))) % MOD;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0; i<=9; i++) {
		//printf("add 1 to %lld, %lld, %lld, %lld at init\n", 1, i%3, i%3==0, i);
		dp[1][i%3][is_369(i)][i]++;
	}
	for(int i=1; i<MX-1; i++) {
		for(int a=0; a<=9; a++) {
			for(int j=0; j<3; j++) {
				for(int k=0; k<2; k++) {
					for(int t=0; t<10; t++) {
						int tj = (j+a)%3, tk = max(k, is_369(a));
						dp[i+1][tj][tk][a] += dp[i][j][k][t];
						dp[i+1][tj][tk][a] %= MOD;
					}
				}
			}
		}
	}
	string a, b;
	cin >> a >> b;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int bv = f(b, (int)b.size()-1, 0, 0);
	//printf("----------------------------------\n");
	do_last = false;
	int av = f(a, (int)a.size()-1, 0, 0);
	//printf("bv=%lld, av=%lld\n", bv, av);
	int ans = bv - av + MOD;
	cout << (ans % MOD);
}
