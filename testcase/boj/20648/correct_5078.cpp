#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
	int x, y;
};
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
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<point> arr(n);
	vector<int> xarr, yarr;
	for(auto &a: arr) {
		cin >> a.x >> a.y;
		xarr.push_back(a.x);
		yarr.push_back(a.y);
	}
	sort(xarr.begin(), xarr.end());
	xarr.erase(unique(xarr.begin(), xarr.end()), xarr.end());
	
	sort(yarr.begin(), yarr.end());
	yarr.erase(unique(yarr.begin(), yarr.end()), yarr.end());
	
	for(auto &a: arr) {
		a.x = lower_bound(xarr.begin(), xarr.end(), a.x) - xarr.begin() + 1;
		a.y = lower_bound(yarr.begin(), yarr.end(), a.y) - yarr.begin() + 1;
	}
	sort(arr.begin(), arr.end(), [](auto a, auto b) {
		return tie(a.x, a.y) < tie(b.x, b.y);
	});
	int ans = 0;
	for(int i=0; i<n; i++) {
		BIT bit(n);
		for(int j=i; j<n; j++) {
			bit.update(arr[j].y, 1);
			int l = arr[i].y, r = arr[j].y;
			if(l > r)
				swap(l, r);
			ans += bit.query(l) * (bit.query(n) - bit.query(r-1));
		}
	}
	cout << ans + 1;
}
