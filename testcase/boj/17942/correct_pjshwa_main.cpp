#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int K[MAX + 1], uk[MAX + 1];
bool vis[MAX + 1];
vector<pii> graph[MAX + 1];
int N, M;

bool check(int mid) {
  memset(vis, 0, sizeof(vis));

  queue<int> q;
  for (int i = 1; i <= N; i++) {
    uk[i] = K[i];
    if (uk[i] <= mid) {
      q.push(i);
      vis[i] = 1;
    }
  }

  int cnt = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    cnt++;

    for (auto [v, w] : graph[u]) {
      if (vis[v]) continue;

      uk[v] -= w;
      if (uk[v] <= mid) {
        q.push(v);
        vis[v] = 1;
      }
    }
  }

  return cnt >= M;
}

void solve() {
  cin >> N >> M;

  int left = INF, right = 0;
  for (int i = 1; i <= N; i++) {
    cin >> K[i];
    left = min(left, K[i]);
    right = max(right, K[i] + 1);
  }

  int R;
  cin >> R;
  while (R--) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u].push_back({v, w});
  }

  while (left < right) {
    int mid = (left + right) / 2;
    if (check(mid)) right = mid;
    else left = mid + 1;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
