#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
int fst[101], snd[65];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int i = 1;
	rep(j,1) fst[i++] = 500;
	rep(j,2) fst[i++] = 300;
	rep(j,3) fst[i++] = 200;
	rep(j,4) fst[i++] = 50;
	rep(j,5) fst[i++] = 30;
	rep(j,6) fst[i++] = 10;
	i = 1;
	rep(j,1) snd[i++] = 512;
	rep(j,2) snd[i++] = 256;
	rep(j,4) snd[i++] = 128;
	rep(j,8) snd[i++] = 64;
	rep(j,16) snd[i++] = 32;
	int T;
	cin >> T;
	while(T--) {
		int a, b;
		cin >> a >> b;
		cout << (fst[a] + snd[b]) * 10000 << '\n';
	}
}
