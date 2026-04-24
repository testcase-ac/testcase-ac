#include <bits/stdc++.h>
using namespace std;
#define int long long
int divide_round(int a, int b) {
    return (a + b / 2) / b;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int W, H, N;
    cin >> W >> H >> N;
    vector<pair<int, int>> v(N), vx, vy;
    for(int i = 0; i < N; i++) {
        cin >> v[i].first >> v[i].second;
    }
    vx = v;
    vy = v;
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });
    int ax = 0, ay = 0, ans = LLONG_MAX;
    auto check_ans = [&](int x, int y) {
        int total = 0, farthest = 0;
        for(int i = 0; i < N; i++) {
            int dist = abs(v[i].first - x) + abs(v[i].second - y);
            total += dist;
            farthest = max(farthest, dist);
        }
        total *= 2;
        total -= farthest;
        if(total < ans) {
            ans = total;
            ax = x;
            ay = y;
        }
    };
    if(N & 1) {
        check_ans(vx[N / 2].first, vy[N / 2].second);
    } else {
        check_ans(vx[N / 2 - 1].first, vy[N / 2 - 1].second);
        check_ans(vx[N / 2 - 1].first, vy[N / 2].second);
        check_ans(vx[N / 2].first, vy[N / 2 - 1].second);
        check_ans(vx[N / 2].first, vy[N / 2].second);
    }
    cout << ans << '\n';
    cout << ax << ' ' << ay << '\n';
}
