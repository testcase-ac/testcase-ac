#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	ll a, b, c;
	cin >> a >> b >> c;
	ll ans = 1;
	vector<ll> fac(32);
	fac[0] = a;
	for(int i=1; i<32;i++){
		fac[i] = (fac[i-1] * fac[i-1]) % c;
	}
	rep(i, 32) {
		if(b % 2) {
			ans *= fac[i];
			ans %= c;
		}
		b /= 2;
	} 
	cout << ans;
}
