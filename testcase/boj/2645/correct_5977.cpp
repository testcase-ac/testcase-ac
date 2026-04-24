#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
    int r, c;
};
struct elem {
    int r, c, w;
    bool operator<(const elem &o) const {
        return w > o.w;
    }
};
bool seen[51][51];
int dist[51][51], dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
int N, K, H;

int cost(int i, int j) {
    return seen[i][j] ? K : 1;
}
point prv[51][51];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    point st, ed;
    cin >> st.r >> st.c >> ed.r >> ed.c >> K >> H;
    for(int i = 0; i < H; i++) {
        int cnt;
        cin >> cnt;
        point cur, nxt;
        cin >> cur.r >> cur.c;
        cnt--;
        while(cnt--) {
            cin >> nxt.r >> nxt.c;
            for(int r = min(cur.r, nxt.r); r <= max(cur.r, nxt.r); r++) {
                for(int c = min(cur.c, nxt.c); c <= max(cur.c, nxt.c); c++) {
                    seen[r][c] = true;
                }
            }
            cur = nxt;
        }
    }
    priority_queue<elem> pq;
    pq.push({st.r, st.c, cost(st.r, st.c)});
    memset(dist, 0x3f, sizeof dist);
    dist[st.r][st.c] = cost(st.r, st.c);
    while(!pq.empty()) {
        elem cur = pq.top();
        pq.pop();
        if(cur.r == ed.r && cur.c == ed.c) {
            cout << cur.w << '\n';
            point t = ed;
            vector<point> ans;
            while(t.r != st.r || t.c != st.c) {
                ans.push_back(t);
                t = prv[t.r][t.c];
            }
            ans.push_back(st);
            reverse(ans.begin(), ans.end());
            vector<point> ansv;

            ansv.push_back(st);
            for(int i = 1; i + 1 < ans.size(); i++) {
                if((ans[i].r == ans[i - 1].r) != (ans[i + 1].r == ans[i].r)) {
                    ansv.push_back(ans[i]);
                }
            }
            ansv.push_back(ed);
            cout << ansv.size() << ' ';
            for(auto [r, c]: ansv) {
                cout << r << ' ' << c << ' ';
            }
            return 0;
        }
        if(cur.w > dist[cur.r][cur.c]) {
            continue;
        }
        for(int i = 0; i < 4; i++) {
            int nr = cur.r + dr[i], nc = cur.c + dc[i];
            if(nr < 1 || nr > N || nc < 1 || nc > N) {
                continue;
            }
            int w = cur.w + cost(nr, nc);
            if(w < dist[nr][nc]) {
                dist[nr][nc] = w;
                prv[nr][nc] = {cur.r, cur.c};
                pq.push({nr, nc, w});
            }
        }
    }
}
