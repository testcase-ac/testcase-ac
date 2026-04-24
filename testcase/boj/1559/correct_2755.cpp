#include <bits/stdc++.h>
using namespace std;
char arr[100][101];
pair<int, int> dir[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

pair<int, int> nxt_pos(int r, int c, int t) {
    int i = 0;
    switch(arr[r][c]) {
        case 'N':
            i = 0;
            break;
        case 'E':
            i = 1;
            break;
        case 'S':
            i = 2;
            break;
        case 'W':
            i = 3;
            break;
    }
    auto pr = dir[(i + t) % 4];
    return {r + pr.first, c + pr.second};
}

int dist[100][100][256];
vector<pair<int, int>> treasures;
struct state {
    int r, c, bm, w;
    bool operator<(const state &o) const {
        return w > o.w;
    }
};
int R, C;
state next_state(int r, int c, int bm, int t) {
    auto [nr, nc] = nxt_pos(r, c, t);
    if(nr < 0 || nr >= R || nc < 0 || nc >= C)
        return {-1, -1, -1, -1};
    auto it = find(treasures.begin(), treasures.end(), make_pair(nr, nc));
    if(it != treasures.end()) {
        int nbm = bm | (1 << (it - treasures.begin()));
        return {nr, nc, nbm, t + 1};
    }
    return {nr, nc, bm, t + 1};
}

void solve() {
    cin >> R >> C;
    if(!R && !C)
        exit(0);
    for(int i = 0; i < R; i++)
        cin >> arr[i];
    int K;
    cin >> K;
    treasures.resize(K);
    for(auto &[a, b]: treasures) {
        cin >> a >> b;
        a--, b--;
    }
    memset(dist, 0x3f, sizeof(dist));
    priority_queue<state> pq;
    pq.push({0, 0, 0, 0});
    dist[0][0][0] = 0;
    auto add_state = [&](state s) {
        if(s.r == -1)
            return;
        if(dist[s.r][s.c][s.bm] > s.w) {
            dist[s.r][s.c][s.bm] = s.w;
            pq.push(s);
        }
    };
    while(pq.size()) {
        auto [r, c, bm, w] = pq.top();
        pq.pop();
        if(w > dist[r][c][bm])
            continue;
        add_state(next_state(r, c, bm, w));
        add_state(next_state(r, c, bm, w + 1));
        add_state(next_state(r, c, bm, w + 2));
        add_state(next_state(r, c, bm, w + 3));
    }
    cout << dist[R - 1][C - 1][(1 << K) - 1] << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    while(1) {
        solve();
    }
}
