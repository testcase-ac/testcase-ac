#include <bits/stdc++.h>
#define int long long
using namespace std;
int lsb(int i) {return i&(-i);}
struct BIT {
    vector<int> bit;
    int n;
    BIT() {};
    BIT(int _n) { bit.resize(_n+1); n=_n;};
    void update(int i, int v) {
        while(i <= n) {
            bit[i] += v;
            i += lsb(i);
        }
    };
    int query(int i) {
        int ret = 0;
        while(i) {
            ret += bit[i];
            i -= lsb(i);
        }
        return ret;
    };
};
struct query {
	int l, r, i;
};
const int MX = 100001, SQRT = sqrt(MX);
int arr[MX], ans[MX], cur, K;
query qry[MX];
BIT bit(MX);
void add(int t) {
	cur += bit.query(min(t+K, MX)) - bit.query(max(t-K-1, 0ll));
	bit.update(t, 1);
}
void sub(int t) {
	bit.update(t, -1);
	cur -= bit.query(min(t+K, MX)) - bit.query(max(t-K-1, 0ll));
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n >> K;
	for(int i=1; i<=n; i++) {
		cin >> arr[i];
	}
	int q;
	cin >> q;
	for(int i=0; i<q; i++) {
		auto& [l, r, t] = qry[i];
		cin >> l >> r;
		t = i;
	}
	sort(qry, qry+q, [](auto a, auto b){return make_pair(a.l/SQRT, a.r) < make_pair(b.l/SQRT, b.r);});
	int l = 1, r = 0;
	for(int i=0; i<q; i++) {
		auto [ql, qr, qi] = qry[i];
		while(r < qr) {
			r++;
			add(arr[r]);
		}
		while(l > ql) {
			l--;
			add(arr[l]);
		}
		while(r > qr) {
			sub(arr[r]);
			r--;
		}
		while(l < ql) {
			sub(arr[l]);
			l++;
		}
		ans[qi] = cur;
	}
	for(int i=0; i<q; i++) {
		cout << ans[i] << '\n';
	}
}
