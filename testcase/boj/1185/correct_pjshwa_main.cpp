#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

const int MAX = 1e4;
bool vis[MAX + 1];
int wt[MAX + 1];
vector<pii> graph[MAX + 1];
int main() {
  int v, e, a, b, c;
  cin >> v >> e;

  for (int i = 1; i <= v; i++) cin >> wt[i];
  for (int i = 0; i < e; i++) {
    cin >> a >> b >> c;
    int new_wt = 2 * c + wt[a] + wt[b];
    graph[a].push_back({new_wt, b});
    graph[b].push_back({new_wt, a});
  }

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, 1});

  // Prim's algorithm
  ll ans = 0;
  int wgt, vtx, wgt_d, vtx_d;
  while (!pq.empty()) {
    tie(wgt, vtx) = pq.top();
    pq.pop();

    if (vis[vtx]) continue;
    vis[vtx] = true;
    ans += wgt;

    for (auto &x : graph[vtx]) {
      tie(wgt_d, vtx_d) = x;
      if (!vis[vtx_d]) pq.push({wgt_d, vtx_d});
    }
  }

  cout << (ans + *min_element(wt + 1, wt + v + 1));
}
