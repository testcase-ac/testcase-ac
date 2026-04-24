#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<pair<int, int>> ans;
void rec(int t) {
    if(t == 1) {
        ans.push_back({-1, -1}); // 1: t
        ans.push_back({0, 0}); // 2: t+1
        return;
    }
    rec(t / 2); // t/2, t/2+1
    int t2 = ans.size() - 2, t2p1 = ans.size() - 1;
    if(t % 2 == 0) { // 4
        ans.push_back({t2, t2}); // t -> 2 + 2
        ans.push_back({t2p1, t2}); // t+1 -> 3 + 2
    } else { // 5
        ans.push_back({t2p1, t2}); // 3 2
        ans.push_back({t2p1, t2p1}); // 3 3
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    while(N--) {
        int t;
        cin >> t;
        ans.clear();
        rec(t);
        cout << ans.size() << '\n';
        for(auto [a, b]: ans) {
            cout << a << ' ' << b << '\n';
        }
        cout << ans.size() - 2 << '\n';
    }
}
