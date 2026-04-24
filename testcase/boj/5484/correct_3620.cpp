#include <bits/stdc++.h>
using namespace std;
int ARR[251][251], ACC[251][251], C, R, N, K;
int r1_dp[252], r2_dp[252], c1_dp[252], c2_dp[252];
int get_sum(int r1, int c1, int r2, int c2) {
    return ACC[r2][c2] - ACC[r1 - 1][c2] - ACC[r2][c1 - 1] + ACC[r1 - 1][c1 - 1];
}
int get(int r, int c1, int c2) {
    int lo = r, hi = R;
    while(lo < hi) {
        int mid = (lo + hi) / 2;
        if(get_sum(r, c1, mid, c2) >= K)
            hi = mid;
        else
            lo = mid + 1;
    }
    int sm = get_sum(r, c1, lo, c2);
    if(sm != K)
        return 0;
    return lo;
}
struct rect {
    int r1, c1, r2, c2;
    bool is_overlap(rect &r) {
        return !(r1 > r.r2 || r.r1 > r2 || c1 > r.c2 || r.c1 > c2);
    }
    int perimeter() {
        return 2 * (r2 - r1 + c2 - c1 + 2);
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    rect r1 = {1, 1, 2, 2}, r2 = {2, 2, 3, 3};
    cin >> R >> C >> N >> K;
    for(int i = 1; i <= N; i++) {
        int r, c;
        cin >> r >> c;
        ARR[r][c]++;
    }
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            ACC[i][j] = ACC[i - 1][j] + ACC[i][j - 1] - ACC[i - 1][j - 1] + ARR[i][j];
        }
    }
    vector<rect> v;
    memset(r1_dp, 0x3f, sizeof(r1_dp));
    memset(r2_dp, 0x3f, sizeof(r2_dp));
    memset(c1_dp, 0x3f, sizeof(c1_dp));
    memset(c2_dp, 0x3f, sizeof(c2_dp));
    auto add_rect = [&](int r1, int c1, int r2, int c2) {
        rect r = {r1, c1, r2, c2};
        v.push_back(r);
        int p = r.perimeter();
        r1_dp[r1] = min(r1_dp[r1], p);
        r2_dp[r2] = min(r2_dp[r2], p);
        c1_dp[c1] = min(c1_dp[c1], p);
        c2_dp[c2] = min(c2_dp[c2], p);
    };
    for(int r = 1; r <= R; r++) {
        for(int c1 = 1; c1 <= C; c1++) {
            for(int c2 = c1; c2 <= C; c2++) {
                if(!get_sum(r, c1, r, c2))
                    continue;
                int g = get(r, c1, c2);
                if(g && get_sum(r, c1, g, c1) && get_sum(r, c2, g, c2)) {
                    add_rect(r, c1, g, c2);
                }
            }
        }
    }

    for(int r = R; r >= 1; r--) {
        r1_dp[r] = min(r1_dp[r], r1_dp[r + 1]);
    }
    for(int r = 1; r <= R; r++) {
        r2_dp[r] = min(r2_dp[r], r2_dp[r - 1]);
    }
    for(int c = C - 1; c >= 1; c--) {
        c1_dp[c] = min(c1_dp[c], c1_dp[c + 1]);
    }
    for(int c = 2; c <= C; c++) {
        c2_dp[c] = min(c2_dp[c], c2_dp[c - 1]);
    }
    int ans = 0x3f3f3f3f;
    for(int i = 0; i < v.size(); i++) {
        ans = min(ans, v[i].perimeter() + r1_dp[v[i].r2 + 1]);
        ans = min(ans, v[i].perimeter() + r2_dp[v[i].r1 - 1]);
        ans = min(ans, v[i].perimeter() + c1_dp[v[i].c2 + 1]);
        ans = min(ans, v[i].perimeter() + c2_dp[v[i].c1 - 1]);
    }
    if(ans == 0x3f3f3f3f)
        cout << "NO";
    else
        cout << ans;
}
