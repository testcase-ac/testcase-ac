#include <bits/stdc++.h>
using namespace std;
const int MX = 5e5+5, MXLOG = MX * 160;
int R, C, logR, logC, N;
int _mx_table[MXLOG], _mn_table[MXLOG];
void cassert(bool b) {
    if(!b) {
        cout << "assertion failed\n";
        exit(0);
    }
}
int& mx_table(int a, int b, int r, int c) {
    int idx = a * R * C * logC + b * R * C + r * C + c;
    return _mx_table[idx];
}

int& mn_table(int a, int b, int r, int c) {
    int idx = a * R * C * logC + b * R * C + r * C + c;
    return _mn_table[idx];
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> R >> C >> N;
    // max 200: https://en.wikipedia.org/wiki/Highly_composite_number
    vector<int> factors;
    vector<vector<int>> arr(R, vector<int>(C));
    for(int i=1; i<=N; i++) {
        if(N % i == 0) {
            factors.push_back(i);
        }
    }
    int ans = -1;
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cin >> arr[i][j];
        }
    }
    logR = 32 - __builtin_clz(R), logC = 32 - __builtin_clz(C);
    for(int r=0; r<R; r++) {
        for(int c=0; c<C; c++) {
            mx_table(0,0,r,c) = arr[r][c];
            mn_table(0,0,r,c) = arr[r][c];
        }
    }
    for(int a=0; a<logR; a++) {
        for(int b=0; b<logC; b++) {
            for(int r=0; r<R; r++) {
                for(int c=0; c<C; c++) {
                    if(a) {
                        int nr = min(r+(1<<(a-1)), R-1);
                        mx_table(a, b, r, c) = max(mx_table(a-1,b,r,c), mx_table(a-1, b, nr, c));
                        mn_table(a, b, r, c) = min(mn_table(a-1,b,r,c), mn_table(a-1,b, nr, c));
                    }
                    if(b) {
                        int nc = min(c+(1<<(b-1)), C-1);
                        mx_table(a, b, r, c) = max(mx_table(a, b-1, r, c), mx_table(a, b-1, r, nc));
                        mn_table(a, b, r, c) = min(mn_table(a, b-1, r, c), mn_table(a, b-1, r, nc));
                    }
                }
            }
        }
    }
    auto query_mx = [&](int r1, int r2, int c1, int c2) {
        int a = 31 - __builtin_clz(r2 - r1 + 1), b = 31 - __builtin_clz(c2 - c1 + 1);
        return max({
            mx_table(a, b, r1, c1),
            mx_table(a, b, r2-(1<<a)+1, c1),
            mx_table(a, b, r1, c2-(1<<b)+1),
            mx_table(a, b, r2-(1<<a)+1, c2-(1<<b)+1)
        });
    };
    auto query_mn = [&](int r1, int r2, int c1, int c2) {
        int a = 31 - __builtin_clz(r2 - r1 + 1), b = 31 - __builtin_clz(c2 - c1 + 1);
        return min({
            mn_table(a, b, r1, c1),
            mn_table(a, b, r2-(1<<a)+1, c1),
            mn_table(a, b, r1, c2-(1<<b)+1),
            mn_table(a, b, r2-(1<<a)+1, c2-(1<<b)+1)
        });
    };
    for(int br: factors) {
        int bc = N / br;
        if(br > R || bc > C) {
            continue;
        }
        for(int r=0; r+br<=R; r++) {
            for(int c=0; c+bc<=C; c++) {
                int mx = query_mx(r, r+br-1, c, c+bc-1), mn = query_mn(r, r+br-1, c, c+bc-1);
                ans = max(ans, mx - mn);
            }
        }
    }
    cout << ans;
}
