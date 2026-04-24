#include <bits/stdc++.h>
using namespace std;
inline int lsb(int i){return i&-i;}
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
const int MX = 1e6;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	BIT bit(MX);
	while(n--) {
		int a, b, c;
		cin >> a;
		if(a == 1) {
			cin >> b;
			int l = 1, r = MX, mid;
			while(l < r) {
				mid = (l+r)/2;
				int q = bit.query(mid);
				if(q < b)
					l = mid+1;
				else
					r = mid;
			}
			cout << l << '\n';
			bit.update(l, -1);
		} else {
			cin >> b >> c;
			bit.update(b, c);
		}
	}
}
