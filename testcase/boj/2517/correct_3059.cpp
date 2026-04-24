#include <bits/stdc++.h>
using namespace std;
const int MX = 5e5+2;
pair<int, int> arr[MX];
int a[MX];
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
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i].first;
		arr[i].second = i;
	}
	sort(arr, arr+n);
	for(int i=0; i<n; i++) {
		a[arr[i].second] = i+1;
	}
	BIT bit(MX);
	for(int i=0; i<n; i++) {
		cout << (i+1-bit.query(a[i])) << '\n';
		bit.update(a[i], 1);
	}
}
