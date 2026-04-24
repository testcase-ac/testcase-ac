#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5+2;
int arr[MX], acc[MX];
int f(int l, int r) {
	return acc[r] ^ (l ? acc[l-1] : 0);
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		arr[n] ^= arr[i];
		acc[i] = (i ? acc[i-1] : 0) ^ arr[i];
	}
	acc[n] = acc[n-1] ^ arr[n];
	int q;
	cin >> q;
	while(q--) {
		int l, r;
		cin >> l >> r;
		l--, r--;
		int li = l / (n+1), lm = l % (n+1), ri = r / (n+1), rm = r % (n+1);
		//printf("li, lm=%d, %d / ri, rm=%d, %d\n", li, lm, ri, rm);
		if(li == ri) {
			cout << f(lm, rm) << '\n';
		} else {
			cout << (f(lm, n) ^ f(0, rm)) << '\n';
		}
	}
}
