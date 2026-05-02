#include <iostream>
#include <array>
#include <algorithm>

using namespace std;
using i64 = long long;

struct FenwickTree {
    array<int, 1502> arr;
    int n;

    void init(int n) {
        this->n = n;
    }

    int* leaves() { return arr.data()+1; }
    void build() {
        for (int i = 1; i <= n; i++) {
            int ni = i + (i & -i);
            if (ni <= n) { arr[ni] += arr[i]; }
        }
    }

    int query_psum(int i) {
        i++;
        int res = 0;
        while (i >= 1) {
            res += arr[i];
            i -= i & -i;
        }
        return res;
    }

    void update(int i, int x) {
        i++;
        while (i <= n) {
            arr[i] += x;
            i += i & -i;
        }
    }
};

array<FenwickTree, 1501> dp;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    i64 sum = 0;

    for (int y = 1; y <= n; y++) {
        dp[y].init(n+1);
        for (int x = 1; x <= n; x++) {
            int& cur = dp[y].leaves()[x];
            cin >> cur;
            cur += max(dp[y-1].leaves()[x], dp[y].leaves()[x-1]);
            sum += i64(cur);
        }
    }
    
    for (int y = 1; y <= n; y++) {
        for (int x = n; x >= 2; x--) {
            dp[y].leaves()[x] -= dp[y].leaves()[x-1];
        }
        dp[y].build();
    }

    cout << sum << '\n';

    for (int _q = 0; _q < n; _q++) {
        char t; int x0, y0;
        cin >> t >> y0 >> x0;
        
        if (t == 'U') {
            int l = x0, r = x0;
            for (int y = y0; y <= n; y++) {
                if (y != y0) {
                    while (l <= r && dp[y].query_psum(l-1) >= dp[y-1].query_psum(l)) { l++; }
                }
                if (l > r) { break; }
                while (r <= n-1 && dp[y].query_psum(r) >= dp[y-1].query_psum(r+1)) { r++; }
                dp[y].update(l, 1);
                dp[y].update(r+1, -1);
                sum += i64(r-l+1);
            }
        } else {
            int l = x0, r = x0;
            for (int y = y0; y <= n; y++) {
                if (y != y0) {
                    while (l <= r && dp[y].query_psum(l-1) > dp[y-1].query_psum(l)) { l++; }
                }
                if (l > r) { break; }
                while (r <= n-1 && dp[y].query_psum(r) > dp[y-1].query_psum(r+1)) { r++; }
                dp[y].update(l, -1);
                dp[y].update(r+1, 1);
                sum -= i64(r-l+1);
            }
        }

        cout << sum << '\n';
    }

    return 0;
}
