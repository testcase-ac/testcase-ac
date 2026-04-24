#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 505;
int d[MX][MX], S[MX][MX];
struct path {
    int v, w;
    bool operator<(const path& o) const {
        return w < o.w;
    }
};
vector<path> adj[MX];
void dijk(int st) {
    memset(S[st], 0, sizeof S[st]);
    S[st][st] = 1e9;
    priority_queue<path> pq;
    pq.push({st, (int)1e9});
    while(pq.size()) {
        path cur = pq.top();
        pq.pop();
        if(S[st][cur.v] > cur.w) continue;
        for(path nxt : adj[cur.v]) {
            int nxt_w = min(cur.w, nxt.w);
            if(nxt_w > S[st][nxt.v]) {
                S[st][nxt.v] = nxt_w;
                pq.push({nxt.v, nxt_w});
            }
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M, N;
    cin >> M >> N;
    for(int i=0; i<N; i++) {
        vector<int> arr(M);
        for(int j=0; j<M; j++) {
            cin >> arr[j];
        }
        for(int j=0; j<M; j++) {
            for(int k=0; k<M; k++) {
                if((!arr[k] && arr[j]) || (arr[k] && arr[j] && arr[j] < arr[k]))
                    d[j][k]++;
            }
        }
    }
    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            if(d[i][j] > d[j][i]) {
                adj[i].push_back({j, d[i][j]});
            }
        }
    }
    for(int i=0; i<M; i++) {
        dijk(i);
    }
    for(int x=0; x<M; x++) {
        bool ok = 1;
        for(int y=0; y<M; y++) {
            if(x == y) continue;
            if(S[x][y] < S[y][x]) {
                ok = 0;
                break;
            }
        }
        if(ok) {
            cout << x + 1 << ' ';
        }
    }
}
