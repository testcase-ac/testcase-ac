#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
inline int sq(int x) {
    return x*x;
}
struct Point {
    typedef Point P;
    int x, y;
    explicit Point(int x=0, int y=0): x(x), y(y) {}
    bool operator<(const P& p) const {return tie(x, y) < tie(p.x, p.y);}
    bool operator==(const P& p) const {return tie(x, y) == tie(p.x, p.y);}
    Point operator-(Point p) {return Point(x - p.x, y-p.y);}
    int distsq() {return sq(x) + sq(y);}
    int dot(P p) {return x * p.x + y * p.y;}
};

typedef Point P;
int ccw(P a, P b, P c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if(v < 0) return -1;
    if(v > 0) return 1;
    return 0;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    // 0816
    int E;
    cin >> E;
    vector<pair<P, P>> edges(E);
    for(auto &[u, v]: edges) {
        cin >> u.x >> u.y >> v.x >> v.y;
    }
    double ans = 0;
    function<void(P, P)> remove_edge = [&](P a, P b) {
        for(int i=0; i<edges.size(); i++) {
            if(edges[i] == make_pair(a, b) || edges[i] == make_pair(b, a)) {
                // printf("remove edge: %d %d - %d %d\n", a.x, a.y, b.x, b.y);
                edges.erase(edges.begin() + i);
                break;
            }
        }
        int ai = -1, acnt = 0;
        for(int i=0; i<edges.size(); i++) {
            if(edges[i].first == a || edges[i].second == a) {
                acnt++;
                ai = i;
            }
        }
        if(acnt == 1) {
            remove_edge(edges[ai].first, edges[ai].second);
        }
        int bi = -1, bcnt = 0;
        for(int i=0; i<edges.size(); i++) {
            if(edges[i].first == b || edges[i].second == b) {
                bcnt++;
                bi = i;
            }
        }
        if(bcnt == 1) {
            remove_edge(edges[bi].first, edges[bi].second);
        }
    };
    while(edges.size()) {
        // printf("start at edges = %d\n", edges.size());
        set<Point> points_st;
        for(auto [u1, u2]: edges) {
            points_st.insert(u1);
            points_st.insert(u2);
        }
        vector<Point> points(all(points_st));
        vector<vector<int>> adj(points.size());
        for(auto [p1, p2]: edges) {
            int i1 = lower_bound(all(points), p1) - points.begin();
            int i2 = lower_bound(all(points), p2) - points.begin();
            adj[i1].push_back(i2);
            adj[i2].push_back(i1);
        }
        sort(all(adj[0]), [&](int ia, int ib) {
            Point a = points[ia], b = points[ib];
            return ccw(points[0], a, b) < 0;
        });
        int cur = 0, nxt = adj[0][0];
        if(adj[cur].size() == 1) {
            remove_edge(points[cur], points[nxt]);
            continue;
        }
        // printf("  start at %d %d - %d %d\n", points[cur].x, points[cur].y, points[nxt].x, points[nxt].y);
        int area = 0;
        bool ok = 1;
        while(nxt != 0) {
            area += (points[cur].x * points[nxt].y) - (points[cur].y * points[nxt].x);
            if(adj[nxt].size() == 1) {
                ok = 0;
                remove_edge(points[cur], points[nxt]);
                break;
            }
            int cur_i = find(all(adj[nxt]), cur) - adj[nxt].begin();
            swap(adj[nxt][0], adj[nxt][cur_i]);
            int me = min_element(adj[nxt].begin()+1, adj[nxt].end(), [&](int ia, int ib) {
                P a = points[ia], b = points[ib];
                int ca = ccw(points[cur], points[nxt], a), cb = ccw(points[cur], points[nxt], b);
                if(ca != cb) {
                    return ca < cb;
                }
                int cc = ccw(points[nxt], a, b);
                return cc > 0;  // note: cannot be zero, since from same node
            }) - adj[nxt].begin();
            cur = nxt;
            nxt = adj[nxt][me];
            // printf("  moved to %d %d - %d %d\n", points[cur].x, points[cur].y, points[nxt].x, points[nxt].y);
        }
        if(ok) {
            area += (points[cur].x * points[nxt].y) - (points[cur].y * points[nxt].x);
            double realarea = abs(area) / 2.0;
            ans += realarea * realarea;
            // printf("ok, area is %lf\n", realarea);
        } else {
            // printf("not ok\n");
        }
        cur = 0, nxt = adj[0][0];
        remove_edge(points[cur], points[nxt]);
    }
    cout << fixed << setprecision(8) << ans;
}
