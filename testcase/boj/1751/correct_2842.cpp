#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MX = 304, MOD = 1000000007;
int R, C;
ll p3[MX*(MX+1)];
char a[2][MX][MX];
ll h[2][MX][MX];
ll f(ll t) {
	while(t < 0) t += MOD;
	while(t >= MOD) t -= MOD;
	return t;
}
ll h2d(int t, ll i, ll j, ll u, ll v) {
	ll val = f(h[t][i][j] - h[t][u-1][j] - h[t][i][v-1] + h[t][u-1][v-1]);
	return (val * p3[R*C-(u*C+v)]) % MOD;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> R >> C;
	for(int i=1; i<=R; i++) {
		string s;
		cin >> s;
		for(int j=1; j<=C; j++) {
			a[0][i][j] = s[j-1];
		}
	}
	for(int i=1; i<=R; i++) {
		for(int j=1; j<=C; j++) {
			a[1][i][j] = a[0][R+1-i][C+1-j];
		}
	}
	p3[0] = 1;
	for(int i=1; i<MX*MX; i++) {
		p3[i] = (p3[i-1]*3)%MOD;
	}
	for(int k=0; k<2; k++) {
		for(int i=1; i<=R; i++) {
			for(int j=1; j<=C; j++) {
				h[k][i][j] = f(h[k][i-1][j] + h[k][i][j-1] - h[k][i-1][j-1] + p3[i*C+j]*(a[k][i][j]-'0'+1));
			}
		}	
	}
	int ans = 1;
	for(int i=1; i<=R; i++) {
		for(int j=1; j<=C; j++) {
			int u = i, v = j;
			while(--u && --v) {
				if(h2d(0, i, j, u, v) == h2d(1, R+1-u, C+1-v, R+1-i, C+1-j))
					ans = max(ans, i-u+1);
			}
		}
	}
	cout << ans;
}
