#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 720;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M;
    cin >> M;
    vector<int> vec;
    while(M--) {
        string s;
        cin >> s;
        int h = stoi(s.substr(0, 2));
        int m = stoi(s.substr(3, 2));
        vec.push_back((h*60+m)%MOD);
    }
    int ans = INT_MAX;
    for(int r=1; r<=720; r++) {
        vector<int> v = vec;
        for(int i=1; i<v.size(); i++) {
            v[i] = (v[i] - (r * i) % MOD + MOD) % MOD;
        }
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        int cnt = v.size();
        ans = min(ans, cnt);
    }
    cout << ans;
}
