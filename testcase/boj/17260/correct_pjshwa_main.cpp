#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
const ll INF = 1e18;
int H[MAX + 1];
vector<int> graph[MAX + 1];
ll cdist[MAX + 1];
int K;

void dfs(int v, ll add) {
  cdist[v] = add;

  for (int u : graph[v]) {
    ll chgt = H[v] + add;
    ll ndist = 2 * (chgt - H[u]);
    if (cdist[u] > ndist) dfs(u, ndist);
  }
}

void solve() {
  int N;
  cin >> N >> K;
  for (int i = 1; i <= N; i++) cin >> H[i];
  for (int i = 1; i <= N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  fill(cdist, cdist + N + 1, INF);
  dfs(K, 0);
  bool ans = false;
  for (int i = 1; i <= N; i++) {
    if (i == K) continue;
    ans |= (cdist[i] <= 0);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
