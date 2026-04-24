#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define int long long
const int MX = 1001;

struct node {
    int u, w;
    bool operator<(const node& o) const {
        return w > o.w;
    }
};
vector<node> adj[MX];
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    int m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adj[a].push_back({b, w});
    }
    int start, end;
    cin >> start >> end;
    vector<int> dist(n + 1, INT_MAX);
    dist[start] = 0;
    priority_queue<node> pq;
    pq.push({start, 0});
    while(true) {
        node cur = pq.top();
        pq.pop();
        if(cur.u == end) {
            return !(cout << cur.w);
        }
        for(auto nxt: adj[cur.u]) {
            if(dist[nxt.u] > dist[cur.u] + nxt.w) {
                dist[nxt.u] = dist[cur.u] + nxt.w;
                pq.push({nxt.u, dist[nxt.u]});
            }
        }
    }
}
