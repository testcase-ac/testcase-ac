#include <bits/stdc++.h>
using namespace std;
#define int long long
int solve() {
    int N;
    cin >> N;
    int x = 0, y = 0;
    vector<pair<int, int>> v = {{0,0}};
    while(N--) {
        string s;
        int t;
        cin >> s >> t;
        if(s[0] == 'x') {
            x += 2 * t;
        } else if(s[0] == 'y') {
            x += t;
            y += t;
        } else if(s[0] == 'z') {
            x += -t;
            y += t;
        }
        v.push_back({x, y});
    }
    int sm = 0;
    for(int i=0; i<v.size()-1; i++) {
        sm += v[i].first * v[i+1].second - v[i+1].first * v[i].second;
    }
    return abs(sm) / 2;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << solve() << '\n';
    }
}
