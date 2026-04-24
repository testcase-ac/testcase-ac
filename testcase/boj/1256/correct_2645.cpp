#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
#define fastio() ios::sync_with_stdio(false);cin.tie(NULL)

using namespace std;

int nCr[201][201];
int main() {
	fastio();
	for(int i=0; i<=200; i++) nCr[i][0] = nCr[i][i] = 1;
	for(int i=2; i<=200; i++) {
		for(int j=1; j<i; j++) {
			nCr[i][j] = min(MOD, nCr[i-1][j-1]+nCr[i-1][j]);
		}
	}
	int n, m, k;
	cin >> n >> m >> k;
	if(nCr[n+m][n] < k)
		return !(cout << -1);
	int acnt = n;
	for(int i=0; i<(n+m); i++) {
		if(!acnt) {
			cout << 'z';
			continue;
		} else {
			if(nCr[n+m-i-1][acnt-1] < k) { // you still have k left
				k -= nCr[n+m-i-1][acnt-1];
				cout << 'z';
			} else {
				acnt--;
				cout << 'a';
			}
		}
	}
}
