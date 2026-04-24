#include <bits/stdc++.h>
using namespace std;
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
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	BIT bit(100001);
	for(int i=0; i<n; i++) {
		int a, b;
		cin >> a >> b;
		int x = bit.query(a), y = bit.query(b);
		cout << x+y << '\n';
		bit.update(a+1, 1);
		bit.update(b, -1);
		bit.update(a, -x);
		bit.update(a+1, x);
		bit.update(b, -y);
		bit.update(b+1, y);
	}
}
