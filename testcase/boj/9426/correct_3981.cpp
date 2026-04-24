#include <bits/stdc++.h>
using namespace std;
inline int lsb(int i) {return i & -i;}
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
const int MX = 65536;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	int a[n];
	for(int i=0; i<n; i++) {
		cin >> a[i];
		a[i]++;
	}
	BIT bit(MX);
	for(int i=0; i<k-1; i++)
		bit.update(a[i], 1);
	long long ans = 0;
	for(int i=k-1; i<n; i++) {
		bit.update(a[i], 1);
		if(i >= k) bit.update(a[i-k], -1);
		int l = 1, r = MX;
		while(l < r) {
			int mid = (l+r+1)/2;
			int q = bit.query(mid-1);
			if(q < (k+1)/2)
				l = mid;
			else
				r = mid-1;
		}
		ans += l-1;
	}
	cout << ans;
}
