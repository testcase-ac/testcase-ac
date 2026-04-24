#include <bits/stdc++.h>
using namespace std;
const int MX = 50002;
int n, t;
long long ans;
typedef int ll;
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
int st[MX], ed[MX], arr[2*MX], acc[2*MX];
int main() {
	cin >> n;
	BIT bit(2*n+1);
	for(int i=1; i<=2*n; i++) {
		cin >> arr[i];
		if(!st[arr[i]]) {
			st[arr[i]] = i;
			acc[i] = 1;
		} else {
			ed[arr[i]] = i;
		}
	}
	for(int i=2*n; i>=1; i--)
		acc[i] += acc[i+1];
	for(int i=1; i<=2*n; i++) {
		if(st[arr[i]] == i) {
			int add = bit.query(2*n)-bit.query(ed[arr[i]])+acc[ed[arr[i]]];
			ans += add;
			bit.update(ed[arr[i]], 1);
		}
	}
	cout << 1ll*n*(n-1)/2 - ans;
}
