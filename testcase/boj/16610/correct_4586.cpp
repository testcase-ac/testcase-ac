#include <bits/stdc++.h>
using namespace std;
#define int long long
struct info {
    int num, cnt;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, julia;
    cin >> N >> julia;
    map<int, int> mp;
    vector<info> v;
    for(int i=1; i<N; i++) {
        int t;
        cin >> t;
        mp[t]++;
    }
    for(auto [a, b]: mp) {
        v.push_back({a, b});
    }
    int ans = 0;
    while(true) {
        int sz = v.size();
        bool inter;
        if(v.size() == 1) {
            inter = 1;
        } else {
            int dist = (64 - __builtin_clzll(v[sz-1].cnt)) * (v[sz-1].num - v[sz-2].num);
            int j_dist = julia - v[sz-2].num;
            inter = j_dist < dist;
        }
        if(inter) {
            int cyc = 64 - __builtin_clzll(v.back().cnt);
            int k = (julia - v.back().num) / (cyc - 1);
            // printf("ans add %lld\n", k * cyc + (julia - v.back().num) % (cyc - 1));
            ans += k * cyc + (julia - v.back().num) % (cyc - 1);
            break;
        } else {
            int dist = (64 - __builtin_clzll(v[sz-1].cnt)) * (v[sz-1].num - v[sz-2].num);
            ans += dist;
            julia -= dist;
            int tmp = v.back().cnt;
            v.pop_back();
            v.back().cnt += tmp;
            // printf("dist %lld, reduce to %lld %lld\n", dist, v.back().num, v.back().cnt);

        }
    }
    cout << ans;
}
