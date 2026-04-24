#include <bits/stdc++.h>
using namespace std;
#define int long long
int lsb(int i) { return i & (-i); }
struct BIT {
    vector<int> bit;
    int n;
    BIT(){};
    BIT(int _n) {
        bit.resize(_n + 1);
        n = _n;
    };
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
int count_inv(vector<int>& a) {
    BIT bit(a.size());
    int cnt = 0;
    for(int i = (int)a.size() - 1; i >= 0; i--) {
        cnt += bit.query(a[i]);
        bit.update(a[i], 1);
    }
    return cnt;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    BIT bit(10);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int x = count_inv(a), y = count_inv(b);
    cout << (x % 2 == y % 2 ? "Possible" : "Impossible");
}
