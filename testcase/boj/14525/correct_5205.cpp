#include <bits/stdc++.h>
using namespace std;
#define int long long
int mp(char c) {
	switch(c) {
		case 'A': return 1;
		case 'C': return 2;
		case 'T': return 3;
		case 'G': return 4;
	}
}
const int MXC = 5, MOD = 1e9+7, MXN = 502;
int inv[MXN]; // inv of MXC**i
int modinv(int a, int b=MOD-2) {
    int ret = 1, mult = a % MOD;
    while(b) {
        if(b&1) ret = (ret*mult)%MOD;
        mult = (mult*mult)%MOD;
        b /= 2;
    }
    return ret;
}
struct hstring {
	string s;
	vector<int> v;
	void init() {
		v.resize(s.size());
		for(int i=0, p=1; i<s.size(); i++, p = (p*MXC)%MOD) {
			if(i)
				v[i] = v[i-1];
			v[i] += p*mp(s[i]);
			v[i] %= MOD;
		}
	}
	int hsh(int l, int r) {
		return ((v[r]-(l ? v[l-1] : 0)+MOD)%MOD * inv[l]) % MOD;
	}
};
hstring arr[MXN*2];
int n, m;
bool ok(int l, int r) {
	vector<int> v;
	for(int i=0; i<n; i++) {
		v.push_back(arr[i].hsh(l, r));
	}
	sort(v.begin(), v.end());
	for(int i=n; i<2*n; i++) {
		if(binary_search(v.begin(), v.end(), arr[i].hsh(l, r))) {
			return 0;
		}
	}
	return 1;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	for(int i=0, p=1; i<MXN; i++, p=(p*MXC)%MOD)
		inv[i] = modinv(p);
	cin >> n >> m;
	for(int i=0; i<2*n; i++) {
		cin >> arr[i].s;
		arr[i].init();
	}
	int ans = INT_MAX;
	for(int i=0; i<m; i++) {
		int l = i, r = m-1;
		//printf("at i=%d\n", i);
		while(l < r) {
			int mid = (l+r)/2;
			if(ok(i, mid)) {
				r = mid;
			//printf("  check mid=%d, ok, r become %d\n", mid, mid);
			} else {
				l = mid+1;
			//printf("  check mid=%d, not ok, l become %d\n", mid, mid+1);
			}
		}
		if(ok(i, l)) {
			//printf("at i=%d, l=%d\n", i, l);
			ans = min(ans, l-i+1);
		}
	}
	cout << ans;
}
