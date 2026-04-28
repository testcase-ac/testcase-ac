#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>
using namespace std;

bool visited[10001];
vector<pii> graph[10001];
int main() {
  int v, e, a, b, c;
  cin >> v >> e;

  memset(visited, false, sizeof(visited));
  for (int i = 0; i < e; i++) {
    cin >> a >> b >> c;
    graph[a].push_back({c, b});
    graph[b].push_back({c, a});
  }

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, 1});

  // Prim's algorithm
  ll ans = 0;
  int wgt, vtx, wgt_d, vtx_d;
  while (!pq.empty()) {
    tie(wgt, vtx) = pq.top();
    pq.pop();

    if (visited[vtx]) continue;
    visited[vtx] = true;
    ans += wgt;

    for (auto &x : graph[vtx]) {
      tie(wgt_d, vtx_d) = x;
      if (!visited[vtx_d]) pq.push({wgt_d, vtx_d});
    }
  }

  cout << ans << '\n';
}
