#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5 + 1;
int N, R, D, par[MX];
int f(int i) {
    return i == par[i] ? i : par[i] = f(par[i]);
}
void join(int a, int b) {
    a = f(a);
    b = f(b);
    if(a == b) return;
    par[a] = b;
}
struct point {
    int x, y, i;
    bool operator<(const point &p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
};
void solve(vector<point> &v) {
    sort(v.begin(), v.end(), [](const point &a, const point &b) {
        return a.y > b.y;
    });
    set<point> st;
    for(auto [x, y, i]: v) {
        auto it = st.lower_bound({x - R, 0, 0});
        while(it != st.end() && it->x <= x && it->y > y + R + D) {
            it = st.erase(it);
        }
        if(it != st.end() && it->x <= x) {
            join(i, it->i);
        }
        st.insert({x, y, i});
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> R;
    vector<point> v(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i].x >> v[i].y;
        v[i].i = i;
    }
    for(int i = 0; i < N; i++) {
        par[i] = i;
    }
    cin >> D;
    for(int lr = 0; lr < 2; lr++) {
        for(int x = 0; x < 2; x++) {
            for(int y = 0; y < 2; y++) {
                auto k = v;
                for(int i = 0; i < N; i++) {
                    if(x) {
                        k[i].x *= -1;
                    }
                    if(y) {
                        k[i].y *= -1;
                    }
                    if(lr) {
                        swap(k[i].x, k[i].y);
                    }
                }
                solve(k);
            }
        }
    }
    int ans = 0, root_idx = -1;
    for(int i = 0; i < N; i++) {
        if(!v[i].x && !v[i].y) {
            root_idx = i;
            break;
        }
    }
    for(int i = 0; i < N; i++) {
        if(f(root_idx) == f(i)) {
            ans = max(ans, v[i].x + v[i].y + 2 * R);
        }
    }
    cout << ans;
}
