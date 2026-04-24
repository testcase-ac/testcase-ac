#include <bits/stdc++.h>
using namespace std;
#define int long long
int lsb(int i) {return i&(-i);}
struct BIT {
    vector<int> bit;
    int n;
    BIT() {};
    BIT(int _n) { bit.resize(_n+1); n=_n;};
    void update(int i, int v) {
    	if(!i) return;
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
int n, m;
vector<BIT> bit2d;
void update(int i, int j, int v) {
	if(!i) return;
	while(i <= n) {
		bit2d[i].update(j, v);
		i += lsb(i);
	}
}
int query(int i, int j) {
	int ret = 0;
	while(i) {
		ret += bit2d[i].query(j);
		i -= lsb(i);
	}
	return ret;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int q;
	cin >> n >> m >> q;
	bit2d.resize(n+1, m);

	while(q--) {
		int t;
		cin >> t;
		if(t == 1) {
			int x1, x2, y1, y2, d;
			cin >> x1 >> y1 >> x2 >> y2 >> d;
			update(x2+1, y2+1, d);
			update(x1, y1, d);
			update(x1, y2+1, -d);
			update(x2+1, y1, -d);
		} else {
			int x, y;
			cin >> x >> y;
			cout << query(x, y) << '\n';
		}
	}
}
