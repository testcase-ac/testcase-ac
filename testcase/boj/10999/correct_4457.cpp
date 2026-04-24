#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define deb(v) cout << #v << ':' << v

using namespace std;

inline int lsb(int i) {return i & -i;}
struct BIT {
	vector<ll> bit;
	int size;
	BIT() {
		size = 0;
	}
	BIT(int _n) {
		size = _n;
		bit.resize(size+1);
	};
	void update(int i, ll v) {
		while(i <= size) {
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

struct LazyBIT {
	BIT bitadd, bitsub;
	LazyBIT(int _n) {
		bitadd = BIT(_n), bitsub = BIT(_n);
	};
	void update(int l, int r, ll diff) {
		bitadd.update(l, diff);
		bitadd.update(r+1, -diff);
		bitsub.update(l, (l-1)*diff);
		bitsub.update(r+1, -r*diff);
	};
	void ptupdate(int i, ll diff) {
		bitsub.update(i, -diff);
	}
	ll query(int l, int r) {
		return (r*bitadd.query(r)-bitsub.query(r)) - ((l-1)*bitadd.query(l-1)-bitsub.query(l-1));
	}
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m, k;
	cin >> n >> m >> k;
	LazyBIT bit(n);
	rep(i, n) {
		ll t;
		cin >> t;
		bit.ptupdate(i+1, t);
	}
	m += k;
	while(m--) {
		int d;
		cin >> d;
		if(d == 1) {
			int l, r;
			ll diff;
			cin >> l >> r >> diff;
			bit.update(l, r, diff);
		} else {
			int l, r;
			cin >> l >> r;
			cout << bit.query(l,r) << '\n';
		}
	}
}
