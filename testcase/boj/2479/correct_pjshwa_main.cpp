#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
string a[MAX];
vector<int> graph[MAX];
int from[MAX];
bool vis[MAX];

void bfs(int s) {
  memset(vis, 0, sizeof(vis));

  queue<int> q;
  q.push(s);
  vis[s] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int d : graph[u]) {
      if (!vis[d]) {
        vis[d] = true;
        q.push(d);
        from[d] = u;
      }
    }
  }
}

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  int s, e;
  cin >> s >> e;
  s--; e--;

  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    int hdist = 0;
    for (int l = 0; l < k; l++) {
      if (a[i][l] != a[j][l]) hdist++;
    }
    if (hdist == 1) {
      graph[i].push_back(j);
      graph[j].push_back(i);
    }
  }

  memset(from, -1, sizeof(from));
  bfs(s);

  if (vis[e]) {
    stack<int> traj;
    while (from[e] != -1) {
      traj.push(e);
      e = from[e];
    }
    traj.push(s);
    while (!traj.empty()) {
      cout << traj.top() + 1 << ' ';
      traj.pop();
    }
    cout << '\n';
  }
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
