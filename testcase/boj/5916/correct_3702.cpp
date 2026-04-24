#include <bits/stdc++.h>
using namespace std;
#define int long long

const int H = 17, MX = 1 << H;
vector<int> adj[MX];
int parent[MX], depth[MX], heavy[MX], head[MX], pos[MX], cur_pos;
int dfs(int i, int p) {
    int size = 1, max_c_size = 0;
    for(int a: adj[i]) {
        if(a == p)
            continue;
        parent[a] = i;
        depth[a] = depth[i] + 1;
        int c_size = dfs(a, i);
        size += c_size;
        if(c_size > max_c_size) {
            max_c_size = c_size;
            heavy[i] = a;
        }
    }
    return size;
}

void decompose(int i, int h) {
    // printf("node %d has head %d, pos %d\n", i, h, cur_pos);
    head[i] = h;
    pos[i] = cur_pos++;
    if(heavy[i])
        decompose(heavy[i], h);
    for(int a: adj[i]) {
        if(a != parent[i] && a != heavy[i])
            decompose(a, a);
    }
}

int seg[MX * 2];
void seg_update(int l, int r) {
    // printf("seg update on [%d, %d)\n", l, r);
    l += MX, r += MX;
    while(l < r) {
        if(l & 1)
            seg[l++] += 1;
        if(r & 1)
            seg[--r] += 1;
        l >>= 1, r >>= 1;
    }
}
int seg_query(int t) {
    // printf("seg query on %d\n", t);
    t += MX;
    int ans = 0;
    while(t) {
        ans += seg[t];
        t >>= 1;
    }
    return ans;
}

void hld_update(int a, int b) {
    while(head[a] != head[b]) {
        if(depth[head[a]] > depth[head[b]])
            swap(a, b);
        seg_update(pos[head[b]], pos[b] + 1);
        b = parent[head[b]];
    }
    if(depth[a] > depth[b])
        swap(a, b);
    seg_update(pos[a] + 1, pos[b] + 1);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    for(int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, 0);
    decompose(1, 0);
    while(Q--) {
        char c;
        int u, v;
        cin >> c >> u >> v;
        if(c == 'P') {
            hld_update(u, v);
        } else {
            if(depth[u] < depth[v])
                swap(u, v);
            cout << seg_query(pos[u]) << '\n';
        }
    }
}
