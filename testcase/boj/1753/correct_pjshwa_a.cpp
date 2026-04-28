#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct range {
    int _start, _end, _step;
    range(int end) : range(0, end, 1) {}
    range(int start, int end, int step = 1)
        : _start(start), _end(end), _step(step) {}
    struct iterator {
        int i;
        const int step;
        void operator++() { i += step; }
        bool operator!=(const iterator& other) { return i < other.i; }
        int operator*() const { return i; }
    };
    iterator begin() const { return {_start, _step}; }
    iterator end() const { return {_end, _step}; }
};

inline int get_char() {
    static int idx, bytes;
    static char buf[size_t(5e5)];
    if (!(idx - bytes)) {
        bytes = fread(buf, sizeof(char), sizeof(buf), stdin);
        idx = 0;
    }
    return buf[idx++];
}

inline int read_int() {
    int number = 0;
    int c = get_char();
    for (; (c > 47 && c < 58); c = get_char()) number = number * 10 + c - 48;
    return number;
}

int main() {
    int nv = read_int(), ne = read_int(), v_start = read_int();
    struct edge_t {
        int v, w;
    };
    vector<vector<edge_t>> neighbors(nv + 1);
    for (int _ : range(ne)) {
        int u = read_int(), v = read_int(), w = read_int();
        neighbors[u].push_back({v, w});
    }

    constexpr int inf = 1e9;
    vector<int> dist(nv + 1, inf);
    struct vertex_t {
        int dist, idx;
    };
    struct cmp {
        bool operator()(const vertex_t& u, const vertex_t& v) {
            return u.dist > v.dist;
        }
    };
    priority_queue<vertex_t, vector<vertex_t>, cmp> q;
    dist[v_start] = 0;
    q.push({dist[v_start], v_start});
    while (!q.empty()) {
        int u = q.top().idx, d = q.top().dist;
        q.pop();
        if (d != dist[u]) continue;
        for (const auto& edge : neighbors[u]) {
            int v = edge.v, w = edge.w;
            int new_dist = dist[u] + w;
            if (new_dist < dist[v]) {
                dist[v] = new_dist;
                q.push({new_dist, v});
            }
        }
    }
    for (int v : range(1, nv + 1)) {
        if (dist[v] != inf)
            cout << dist[v] << '\n';
        else
            cout << "INF" << '\n';
    }
}
