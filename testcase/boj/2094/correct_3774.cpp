#include <bits/stdc++.h>
using namespace std;
const int MX = 65536, INF = 1e9 + 7;
int N, M, seg[MX * 2];
pair<int, int> observed[MX];
int query(int l, int r) {
    int mx = 0;
    for(l += MX, r += MX; l < r; l >>= 1, r >>= 1) {
        if(l & 1) {
            mx = max(mx, seg[l++]);
        }
        if(r & 1) {
            mx = max(mx, seg[--r]);
        }
    }
    return mx;
}
int rain_at_year(int x) {
    auto it = lower_bound(observed, observed + N, make_pair(x, -1));
    if(it == observed + N || it->first != x) {
        return 0;
    }
    return it->second;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i = 0; i < N; i++) {
        auto &[a, b] = observed[i];
        cin >> a >> b;
        seg[i + MX] = b;
    }
    for(int i = MX - 1; i; i--) {
        seg[i] = max(seg[i * 2], seg[i * 2 + 1]);
    }
    cin >> M;
    while(M--) {
        int y, x;
        cin >> y >> x;
        int yi = upper_bound(observed, observed + N, make_pair(y, INF)) - observed;
        int xi = lower_bound(observed, observed + N, make_pair(x, 0)) - observed;
        int mx = query(yi, xi);
        int yr = rain_at_year(y), xr = rain_at_year(x);
        if(!xr && !yr) {
            cout << "maybe\n";
        } else if(!xr && yr) {
            cout << (mx < yr ? "maybe" : "false") << '\n';
        } else if(xr && !yr) {
            cout << (mx < xr ? "maybe" : "false") << '\n';
        } else {
            if(yr < xr) {
                cout << "false\n";
            } else if(mx >= xr) {
                cout << "false\n";
            } else {
                int cnt = xi - yi, required_cnt = x - y - 1;
                if(cnt == required_cnt) {
                    cout << "true\n";
                } else {
                    cout << "maybe\n";
                }
            }
        }
    }
}
