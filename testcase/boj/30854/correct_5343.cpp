#include <bits/stdc++.h>
using namespace std;
#define int long long
struct elem {
    int x, y;
    bool t;
};
struct point {
    int x, y, lx, rx;
    bool operator<(const point &p) const {
        return tie(y, x) > tie(p.y, p.x);
    }
};

#define all(x) x.begin(), x.end()
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M, N;
    cin >> M >> N;
    vector<elem> wall;
    vector<point> points(N);
    int cx = 0, cy = 0;
    for(int i=0; i<M; i++) {
        if(i&1) {
            int y;
            cin >> y;
            if(y > cy) {
                wall.push_back({cx, cy, 0});
            } else {
                wall.push_back({cx, y, 1});
            }
            cy = y;
        } else {
            cin >> cx;
        }
    }
    for(auto &[x, y, _, __]: points) {
        cin >> x >> y;
    }
    sort(all(points), [](auto a, auto b) {return a.y < b.y;});
    sort(all(wall), [](auto a, auto b){return a.y < b.y;});
    int ptr = 0;
    set<int> stl, str;
    for(auto &[x, y, lx, rx]: points) {
        // printf("handle x, y = %d %d\n", x, y);
        while(ptr < wall.size() && (wall[ptr].y < y || !wall[ptr].y)) {
            // printf("inserted at x = %d\n", wall[ptr].x);
            if(wall[ptr].t) {
                str.insert(wall[ptr].x);
            } else {
                stl.insert(wall[ptr].x);
            }
            ptr++;
        }
        auto itl = prev(stl.upper_bound(x));
        auto itr = str.lower_bound(x);
        lx = *itl;
        rx = *itr;
    }
    set<point> st;
    set<pair<int, int>> st_xy;
    for(auto &p: points) {
        st.insert(p);
        st_xy.insert({p.x, p.y});
    }
    int ans = 0;
    while(st.size()) {
        auto [x, y, lx, rx] = *st.begin(); // get max y
        // printf("at x = %d, y = %d, lx = %d, rx = %d\n", x, y, lx, rx);
        auto it = st_xy.lower_bound({lx, 0});
        while(it != st_xy.end() && it->first <= rx) {
            int cnt = st.erase({it->first, it->second, -1, -1});
            assert(cnt);
            // printf("erased %d %d\n", it->first, it->second);
            it = st_xy.erase(it);
        }
        ans++;
    }
    cout << ans;
}
