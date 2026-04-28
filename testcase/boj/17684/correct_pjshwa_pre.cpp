#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20, INF = 0x3f3f3f3f;
bool A[MAXN + 1][MAXN + 1], V[MAXN + 1][MAXN + 1];
int N, K, W0, Wc = INF;
vector<pii> E;

int distance_sums() {
  int ret = 0;
  for (int s = 1; s <= N; ++s) {
    vector<int> d(N + 1, -1);
    queue<int> q; q.push(s); d[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int v = 1; v <= N; ++v) {
        if (!A[u][v] && !V[u][v]) continue;
        if (d[v] == -1) d[v] = d[u] + 1, q.push(v);
      }
    }
    for (int i = 1; i <= N; ++i) {
      assert(d[i] != -1);
      ret += d[i];
    }
  }
  return ret;
}

void dfs(int l, int ei) {
  if (ei == E.size()) return;

  if (l == K) {
    int tot = distance_sums();
    if (Wc > tot) {
      Wc = tot;
      cout << "new min: " << Wc << '\n';
      for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) {
        if (V[i][j]) cout << i << ' ' << j << '\n';
      }
      cout << flush;
    }
    return;
  }

  // add edge
  for (int nei = ei; nei < E.size(); ++nei) {
    auto [i, j] = E[nei];
    V[i][j] = V[j][i] = true;
    dfs(l + 1, nei + 1);
    V[i][j] = V[j][i] = false;
  }
}

void solve() {
  cin >> N >> K >> W0;
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    A[u][v] = A[v][u] = true;
  }

  for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) {
    if (!A[i][j]) E.emplace_back(i, j);
  }

  dfs(0, 0);
  cout << Wc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
