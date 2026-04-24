#include <bits/stdc++.h>
using namespace std;
#define int long long
struct student {
    int u, a, b, c, d, pr, pc;
    void read() {
        cin >> u >> a >> b >> c >> d;
    }
};
int arr[20][20];
int dr[4] = {0, 0, 1, -1};
int dc[4] = {1, -1, 0, 0};
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<student> students(n * n);
    for(int i = 0; i < n * n; i++) {
        student& s = students[i];
        s.read();
        vector<pair<int, int>> v;
        for(int r = 0; r < n; r++) {
            for(int c = 0; c < n; c++) {
                if(!arr[r][c])
                    v.push_back({r, c});
            }
        }
        auto count_abcd = [&](int r, int c) {
            int cnt = 0, empty = 0;
            for(int k = 0; k < 4; k++) {
                int tr = r + dr[k], tc = c + dc[k];
                if(0 <= tr && tr < n && 0 <= tc && tc < n) {
                    if(arr[tr][tc] == s.a || arr[tr][tc] == s.b || arr[tr][tc] == s.c || arr[tr][tc] == s.d)
                        cnt++;
                    else if(arr[tr][tc] == 0)
                        empty++;
                }
            }
            return cnt * 10000 + empty;
        };
        auto [r_mn, c_mn] = *max_element(v.begin(), v.end(), [&](auto& a, auto& b) {
            auto [r1, c1] = a;
            auto [r2, c2] = b;
            int cnt1 = count_abcd(r1, c1);
            int cnt2 = count_abcd(r2, c2);
            if(cnt1 != cnt2)
                return cnt1 < cnt2;
            return tie(r1, c1) > tie(r2, c2);
        });
        arr[r_mn][c_mn] = s.u;
        s.pr = r_mn;
        s.pc = c_mn;
    }

    int ans = 0;
    for(auto& s: students) {
        // sum any abcd surrounding
        int cnt = 1;
        for(int k = 0; k < 4; k++) {
            int tr = s.pr + dr[k], tc = s.pc + dc[k];
            if(0 <= tr && tr < n && 0 <= tc && tc < n) {
                if(arr[tr][tc] == s.a || arr[tr][tc] == s.b || arr[tr][tc] == s.c || arr[tr][tc] == s.d)
                    cnt *= 10;
            }
        }
        ans += cnt / 10;
    }
    cout << ans;
}
