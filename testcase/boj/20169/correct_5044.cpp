#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
    int x, y;
    bool operator<(const point& p) const {
        return tie(x, y) < tie(p.x, p.y);
    }
    bool operator==(const point& p) const {
        return tie(x, y) == tie(p.x, p.y);
    }
};

const int MX = 505;
map<point, vector<point>> adj;
vector<pair<point, int>> nodes[MX];
vector<point> lines[MX];
bool is_horizontal(vector<point> &v) {
    return v[0].y == v[1].y;
}
point intersect(vector<point> v1, vector<point> v2) {
    if(is_horizontal(v1) == is_horizontal(v2)) return {-1, -1};
    if(!is_horizontal(v1)) swap(v1, v2);
    if(v1[0].x <= v2[0].x && v2[0].x <= v1[1].x && v2[0].y <= v1[0].y && v1[0].y <= v2[1].y) {
        return {v2[0].x, v1[0].y};
    }
    return {-1, -1};
}
int dist(point p1, point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, T;
    cin >> N >> T;
    point cur;
    for (int i = 0; i < N; i++) {
        int bx, by, ex, ey;
        cin >> bx >> by >> ex >> ey;
        point b = {bx, by}, e = {ex, ey};
        lines[i].push_back(b);
        lines[i].push_back(e);
        if(!i) {
            cur = b;
        }
        sort(lines[i].begin(), lines[i].end());
        for(int j=0; j<i; j++) {
            point inter = intersect(lines[i], lines[j]);
            if(inter.x == -1) continue;
            nodes[i].push_back({inter, j});
            nodes[j].push_back({inter, i});
        }
    }
    for(int i=0; i<N; i++) {
        nodes[i].push_back({lines[i][0], -1});
        nodes[i].push_back({lines[i][1], -1});
        sort(nodes[i].begin(), nodes[i].end());
    }
    for(int i=0; i<N; i++) {
        auto &node = nodes[i];
        // assert(node.front().second == -1);
        // assert(node.back().second == -1);
        adj[node[0].first].push_back(node[1].first);
        adj[node.back().first].push_back((node.end()-2)->first);
        for(int j=1; j<node.size()-1; j++) {
            int itn_line  = node[j].second;
            if(adj[node[j].first].size()) continue;
            pair<point, int> p = {node[j].first, -1ll};
            auto it = lower_bound(nodes[itn_line].begin(), nodes[itn_line].end(), p);
            // tleassert(it != nodes[itn_line].end());
            // tleassert(it+1 != nodes[itn_line].end());
            // tleassert(it != nodes[itn_line].begin());
            if(is_horizontal(lines[i])) {
                adj[node[j].first].push_back(node[j-1].first);
                adj[node[j].first].push_back((it+1)->first);
                adj[node[j].first].push_back(node[j+1].first);
                adj[node[j].first].push_back((it-1)->first);
            } else {
                adj[node[j].first].push_back(node[j-1].first);
                adj[node[j].first].push_back((it-1)->first);
                adj[node[j].first].push_back(node[j+1].first);
                adj[node[j].first].push_back((it+1)->first);  
            }
        }
    }
    int t = 0;
    vector<point> route = {cur};
    while(1) {
        if(adj[cur].size() == 1) {
            cur = adj[cur][0];
        } else {
            auto it = find(adj[cur].begin(), adj[cur].end(), route[route.size()-2]);
            // assert(it != adj[cur].end());
            it++;
            if(it == adj[cur].end()) {
                it = adj[cur].begin();
            }
            cur = *it;
        }
        t += dist(route.back(), cur);
        route.push_back(cur);
        if(route.back() == route.front()) {
            break;
        }
    }
    T %= t;
    for(auto &p: route) {
        int d = dist(p, cur);
        if(!d) continue;
        if(d >= T) {
            cout << cur.x + (p.x - cur.x) * T / d << " " << cur.y + (p.y - cur.y) * T / d << "\n";
            return 0;
        } else {
            T -= d;
            cur = p;
        }
    }
}
