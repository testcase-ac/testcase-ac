#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
vector<pii> graph[MAX];
int dx[MAX], dm[MAX], smax = 0, smin = INF;

void dfs(int v, int p) {
  priority_queue<int, vector<int>, greater<int>> top2;
  priority_queue<int> bot2;

  for (auto [u, w] : graph[v]) {
    if (u == p) continue;

    dfs(u, v);
    top2.push(dx[u] + w);
    bot2.push(dm[u] + w);
    if (top2.size() > 2) top2.pop();
    if (bot2.size() > 2) bot2.pop();
  }

  int cmin = 0, cmax = 0;
  if (top2.size() == 1) {
    cmax = top2.top(), cmin = bot2.top();
    if (v == 0) {
      smax = max(smax, cmax);
      smin = min(smin, cmin);
    }
  }
  else if (top2.size() == 2) {
    int omax = top2.top(), omin = bot2.top();
    top2.pop(); bot2.pop();
    cmax = top2.top(), cmin = bot2.top();
    smax = max(smax, cmax + omax);
    smin = min(smin, cmin + omin);
  }

  dx[v] = cmax;
  dm[v] = cmin;
}

void solve() {
  int N;
  cin >> N;

  for (int i = 1; i <= N - 1; i++) {
    int p, q, w;
    cin >> p >> q >> w;
    graph[p].push_back({q, w});
    graph[q].push_back({p, w});
  }

  dfs(0, -1);
  cout << smax << '\n' << smin << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
