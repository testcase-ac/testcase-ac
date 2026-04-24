#include <bits/stdc++.h>
using namespace std;
#define int long long
#define uniqueize(x)          \
    sort(x.begin(), x.end()); \
    x.erase(unique(x.begin(), x.end()), x.end())

struct point {
    int x, y;
    bool operator<(const point &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator==(const point &p) const {
        return x == p.x && y == p.y;
    }
};
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1}, dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    point cur = {0, 0};
    vector<point> v({{0, 0}});
    vector<pair<point, point>> e;
    string s;
    cin >> s;
    for(char c: s) {
        int dir = c - '0';
        point nxt = {cur.x + dx[dir], cur.y + dy[dir]};
        v.push_back(nxt);
        e.push_back(cur < nxt ? make_pair(cur, nxt) : make_pair(nxt, cur));
        cur = nxt;
    }
    uniqueize(v);
    uniqueize(e);
    int cross = 0;
    for(int i = 0; i < e.size(); i++) {
        auto [a, b] = e[i];
        if(a.x + 1 == b.x && a.y + 1 == b.y) {
            point c = {a.x, a.y + 1};
            point d = {a.x + 1, a.y};
            if(binary_search(e.begin(), e.end(), make_pair(c, d))) {
                cross++;
            }
        }
    }
    cout << 1 + e.size() - v.size() + cross;
}
