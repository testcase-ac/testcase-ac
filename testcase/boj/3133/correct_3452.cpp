#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = 1e9 + 7;
struct point {
    int x, y;
};
struct elem {
    int dp, cnt;
    elem combine(elem &other) {
        if(dp == other.dp) {
            return {dp, (cnt + other.cnt) % MOD};
        }
        return dp > other.dp ? *this : other;
    }
};
int N;

void compress(vector<point> &v) {
    map<int, int> xmap, ymap;
    for(int i = 0; i < N; i++) {
        xmap[v[i].x] = 0;
        ymap[v[i].y] = 0;
    }
    int idx = 0;
    for(auto &pr: xmap) {
        pr.second = idx++;
    }
    idx = 0;
    for(auto &pr: ymap) {
        pr.second = idx++;
    }
    for(int i = 0; i < N; i++) {
        v[i].x = xmap[v[i].x];
        v[i].y = ymap[v[i].y];
    }
}

const int MX = 1 << 19;
elem seg[MX * 2];

void update(int t, elem e) {
    t += MX;
    seg[t] = seg[t].combine(e);
    while(t > 1) {
        t /= 2;
        seg[t] = seg[t * 2].combine(seg[t * 2 + 1]);
    }
}

elem query(int l, int r) {
    l += MX;
    r += MX;
    elem ret = {0, 1};
    while(l < r) {
        if(l & 1)
            ret = ret.combine(seg[l++]);
        if(r & 1)
            ret = ret.combine(seg[--r]);
        l /= 2, r /= 2;
    }
    return ret;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    vector<point> v(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i].x >> v[i].y;
    }
    compress(v);
    sort(v.begin(), v.end(), [](point &a, point &b) {
        return tie(a.y, a.x) < tie(b.y, b.x);
    });

    elem ans = {0, 1};
    for(int i = 0, j = 0; i < N; i = j) {
        while(j < N && v[i].y == v[j].y) {
            j++;
        }
        vector<elem> to_update;
        for(int t = i; t < j; t++) {
            elem e = query(0, v[t].x);
            e.dp++;
            to_update.push_back(e);
            ans = ans.combine(e);
        }
        for(int t = i; t < j; t++) {
            update(v[t].x, to_update[t - i]);
        }
    }
    cout << ans.dp << '\n'
         << ans.cnt;
}
