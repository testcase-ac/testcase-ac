#include <bits/stdc++.h>
using namespace std;
#define int long long
struct range {
    int a, c, b;
    int len(int ub) {
        return max(0ll, (min(c, ub) - a + b) / b);
    }
};
vector<range> v;
int calc(int ub) {
    int sum = 0;
    for(auto &k: v) {
        sum += k.len(ub);
    }
    return sum;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    v.resize(n);
    for(auto &[a, c, b]: v) {
        cin >> a >> c >> b;
    }
    int l = 1, r = 2147483647;
    while(l < r) {
        int m = (l + r) / 2;
        int cnt = calc(m);
        if(cnt % 2 == 1) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    int t = calc(l), tp = calc(l - 1);
    if(t % 2 == 0) {
        return !(cout << "NOTHING");
    }
    cout << l << ' ' << t - tp;
}
