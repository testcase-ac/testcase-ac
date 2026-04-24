#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0; i<(n); i++)

const int MAXN = 50, MOD = 31991;
struct Matrix {
	int v[MAXN][MAXN];
	int n;
	Matrix(int _n) {
		n = _n;
		memset(v, 0, sizeof v);
	}
	Matrix operator*(Matrix &m) {
		Matrix ret(n);
		rep(i,n) {
			rep(j,n) {
				rep(k,n) {
					ret.v[i][j] = (ret.v[i][j]+v[i][k]*m.v[k][j]) % MOD;
				}
			}
		}
		return ret;
	}
	int* operator[](int i) {
		return v[i];
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int d, t;
	cin >> d >> t;
	Matrix mult(d), now(d);
	for(int i=0; i<d; i++) {
		mult[0][i] = 1;
	}
	for(int i=1; i<d; i++) {
		mult[i][i-1] = 1;
	}
	for(int i=0; i<d; i++) {
		now[i][i] = 1;	
	}
	while(t) {
		if(t&1) now = now * mult;
		mult = mult * mult;
		t >>= 1;
	}
	cout << now[0][0];
}
