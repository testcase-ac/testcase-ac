#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int> v;
vector<int> dp[512][120];
const int MASK = (1 << 9) - 1;
void prep(int dep, int num, int bm, int w) {
    if(dep == 5) {
        int m = MASK ^ bm;
        int s = m;
        while(s) {
            dp[bm | s][w].push_back(num);
            s = (s - 1) & m;
        }
        dp[bm][w].push_back(num);
        return;
    }
    prep(dep + 1, num * 10, bm, w);

    for(int t: v) {
        int m = 1 << (t - 1);
        if(bm & m) continue;
        prep(dep + 1, num * 10 + t, bm | m, w + (dep + 1) * t);
    }
}

int K, lst;
void solve(int dep, int num, int bm, int w) {
    if(dep == 5) {
        int m = MASK ^ bm;
        auto &vec = dp[m][w];
        sort(vec.begin(), vec.end());
        if(K < vec.size()) {
            cout << vec[K] + num * 100000 << '\n';
            exit(0);
        } else {
            if(vec.size()) {
                lst = vec.back() + num * 100000;
            }
            K -= vec.size();
        }
        return;
    }
    solve(dep + 1, num * 10, bm, w);
    for(int t: v) {
        int m = 1 << (t - 1);
        if(bm & m) continue;
        solve(dep + 1, num * 10 + t, bm | m, w + (5 - dep) * t);
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    v.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    prep(0, 0, 0, 0);

    cin >> K;
    solve(0, 0, 0, 0);

    cout << lst;
}
