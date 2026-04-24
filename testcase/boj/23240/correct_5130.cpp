#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M;
    cin >> M;
    vector<pair<char, int>> v(M);
    for(int i=0; i<M; i++) {
        cin >> v[i].first >> v[i].second;
    }
    reverse(v.begin(), v.end());
    vector<int> cnts(M);
    for(int i=0; i<M; i++) {
        cnts[i] = (1<<i);
    }
    int ans = 0;
    for(int i=0; i<M; i++) {
        auto [c, t] = v[i];
        if(c == 'R' && cnts[i] % 2 == 1) continue;
        if(c == 'B' && cnts[i] % 2 == 0) continue;
        if(c == 'G') continue;
        if(t == 1) continue;
        cnts[i]++;
        if(i == M-1) ans--;
        for(int j=0;i+j+1<M;j++) {
            cnts[i+j+1] += (1<<j);
        }
    }
    for(int i=0; i<M; i++) {
        ans += cnts[i] * v[i].second;
    }
    cout << ans;
}
