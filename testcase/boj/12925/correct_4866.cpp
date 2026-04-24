#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9;
struct Matrix {
    vector<vector<int>> v;
    int n;
    Matrix(int _n) {
        n = _n;
        v = vector<vector<int>>(n, vector<int>(n, 0));
    }
    Matrix operator*(Matrix &m) {
        Matrix ret(n);
        for(int i=0; i<n; i++) {
        	for(int j=0; j<n; j++) {
        		for(int k=0; k<n; k++) {
        			ret.v[i][j] = (ret.v[i][j]+(v[i][k]%MOD)*(m.v[k][j]%MOD)) % MOD;
        		}
        	}
        }
        return ret;
    }
    vector<int>& operator[](int i) {
        return v[i];
    }
};
Matrix modinv(Matrix a, int b=MOD-2) {
    Matrix ret(2), mult = a;
    for(int i=0; i<2; i++) {
    	ret[i][i] = 1;
    }
    while(b) {
        if(b&1) ret = (ret*mult);
        mult = (mult*mult);
        b /= 2;
    }
    return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	for(int i=0; i<t; i++) {
		int x;
		cin >> x;
		Matrix m(2);
		m[0] = {6, MOD-4};
		m[1] = {1, 0};
		m = modinv(m, x-1);
		printf("Case #%d: %03d\n", i+1, (m[0][0]*6 + m[0][1]*2 + 999)%1000);
	}
}
