#include <bits/stdc++.h>
#ifdef SHARAELONG
#include "../../cpp-header/debug.hpp"
#endif
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void solve() {
    int n, m;
    cin >> n >> m;
    
    queue<int> extra;
    vector<pii> inc;
    vector<pii> dec;
    for (int i=0; i<n; ++i) {
        int t, h;
        cin >> t >> h;
        if (h > m) h = m;
        if (t <= h) inc.push_back({t,h});
        if (t > h) dec.push_back({t,h});
    }
    sort(dec.begin(), dec.end(), [](const pii& a, const pii& b) {
        return a.second < b.second;
    });
    dec.insert(dec.end(), inc.begin(), inc.end());

    int curr = m;
    while (!dec.empty()) {
        auto[t,h] = dec.back();
        dec.pop_back();
        while (t > 1) {
            if (curr >= t) {
                curr -= t-1;
                break;
            }
            t -= curr-1;
            if (extra.empty()) {
                cout << "NO\n";
                return;
            }
            curr = extra.front();
            extra.pop();
        }
        extra.push(h);
    }
    cout << "YES\n";
    return;
}

int main() {
    // freopen("../../test.txt", "r", stdin);
    // freopen("../../test.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin >> cases;
    while (cases--) solve();
}
