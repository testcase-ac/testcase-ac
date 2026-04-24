#include <bits/stdc++.h>
typedef long long ll;
const ll mod = 1000000000;
using namespace std;

struct Matrix {
	ll a[2][2];
	Matrix operator*(const Matrix &m) const{
		Matrix r;
		for(int i=0; i<2; i++) {
			for(int j=0; j<2; j++) {
				r.a[i][j] = 0;
				for(int k=0; k<2; k++) {
					r.a[i][j] += a[i][k]*m.a[k][j];
				}
				r.a[i][j] %= mod;
			}
		}
		return r;
	}
};

ll fibo(ll n) {
	Matrix r, m;
	r.a[0][0] = r.a[1][1] = 0;
	r.a[0][1] = r.a[1][0] = 1;
	m.a[0][0] = 0;
	m.a[0][1] = m.a[1][0] = m.a[1][1] = 1;
	while(n) {
		if(n&1) r = r * m;
		m = m * m;
		n >>= 1;
	}
	return r.a[1][1];
}

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	ll a, b;
	cin >> a >> b;
	cout << (fibo(b+2) - fibo(a+1) + mod) % mod;
}
