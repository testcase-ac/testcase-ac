#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
int lsb(int i) {return i&(-i);}
struct BIT {
    vector<ll> bit;
    int n;
    BIT() {};
    BIT(int _n) { bit.resize(_n+1); n=_n;};
    void update(int i, ll v) {
        while(i <= n) {
            bit[i] += v;
            i += lsb(i);
        }
    };
    ll query(int i) {
        ll ret = 0;
        while(i) {
            ret += bit[i];
            i -= lsb(i);
        }
        return ret;
    };
};
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	BIT fbit(n), bbit(n);
	vector<int> a(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
		bbit.update(a[i], 1);
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		bbit.update(a[i], -1);
		ans += (fbit.query(n) - fbit.query(a[i])) * bbit.query(a[i]-1);
		fbit.update(a[i], 1);
	}
	cout << ans;
}
