#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int C[MAX + 1];
vector<int> graph[MAX + 1];
int N;
bool vis1[MAX + 1], vis2[MAX + 1];

bool check(int p) {
  queue<pii> q;
  memset(vis1, 0, sizeof(vis1));
  memset(vis2, 0, sizeof(vis2));
  for (int i = 1; i <= N; i++) {
    if (!C[i]) {
      q.push({i, 1});
      vis1[i] = true;
    }
  }

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    if (c == p) continue;

    for (int u : graph[v]) {
      if (!vis1[u]) {
        q.push({u, c + 1});
        vis1[u] = true;
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    if (C[i] && !vis1[i]) {
      q.push({i, 1});
      vis2[i] = true;
    }
  }

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    if (c == p) continue;

    for (int u : graph[v]) {
      if (!vis2[u]) {
        q.push({u, c + 1});
        vis2[u] = true;
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    if (C[i] != vis2[i]) return false;
  }
  return true;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> C[i];
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int left = 1, right = N + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (check(mid)) left = mid + 1;
    else right = mid;
  }
  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
