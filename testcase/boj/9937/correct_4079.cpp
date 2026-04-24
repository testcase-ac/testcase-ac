#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;
struct line {
    int a, b;

    void simplify() {
        if(a == 0) {
            b = 1;
            return;
        }
        if(b == 0) {
            a = 1;
            return;
        }
        if(a < 0) {
            a = -a;
            b = -b;
        }
        int g = __gcd(abs(a), abs(b));
        a /= g;
        b /= g;
    }
    bool operator<(const line &o) const {
        return a < o.a || (a == o.a && b < o.b);
    }
    bool operator==(const line &o) const {
        return a == o.a && b == o.b;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<line> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].a >> v[i].b;
        v[i].simplify();
        int c;
        cin >> c;
    }
    vector<int> cnt;
    sort(v.begin(), v.end());
    for(int i = 0, j = 0; i < n; i = j) {
        while(j < n && v[i] == v[j]) j++;
        cnt.push_back(j - i);
    }
    int ans = 0, prod = 0, sum = 0;
    for(int i = 0; i < cnt.size(); i++) {
        ans += cnt[i] * prod;
        prod += cnt[i] * sum;
        sum += cnt[i];
        ans %= MOD;
        prod %= MOD;
        sum %= MOD;
        }
    cout << ans;
}
