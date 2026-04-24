#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e6 + 5;
int nxt[MX], seen[MX], dist[MX], tme[MX];
int cyc_size = -1, st_pt = -1;
void dfs(int i) {
    seen[i] = 1;
    if(nxt[i] >= 0 && seen[nxt[i]] == 2) { // alrdy done
        dist[i] = dist[nxt[i]] + 1;
    } else if(seen[nxt[i]] == 1 || nxt[i] == -1) { // backedge, cycle
        if(nxt[i] == -1) {
            dist[i] = 1;
        } else {
            cyc_size = tme[i] - tme[nxt[i]] + 1;
            st_pt = nxt[i];
            dist[i] = cyc_size;
        }
        //printf("found cyc, st pt = %lld", st_pt);
    } else {
        tme[nxt[i]] = tme[i] + 1;
        dfs(nxt[i]);
        if(cyc_size != -1) {
            dist[i] = cyc_size;
            if(st_pt == i) {
                cyc_size = -1;
            }
        } else {
            dist[i] = dist[nxt[i]] + 1;
        }
    }
    //printf("dfs: dist %lld = %lld\n", i, dist[i]);
    seen[i] = 2;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int M, N;
    cin >> M >> N;
    memset(nxt, -1, sizeof nxt);
    for(int i=0; i<M; i++) {
        int u, v;
        cin >> u >> v;
        nxt[u] = v;
    }
    int ans = 0;
    vector<int> stk;
    for(int i=0; i<N; i++) {
        if(seen[i]) continue;
        cyc_size = -1;
        dfs(i);
        //printf("dist %lld = %lld\n", i, dist[i]);
        ans = max(ans, dist[i]);
    }
    cout << ans;
}
