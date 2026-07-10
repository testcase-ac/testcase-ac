#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
vector<int> adj[MAXN + 1];
int V[MAXN + 1];
deque<int> O;

void dfs(int v, int p, int e) {
  V[v] = e;
  for (int u : adj[v]) {
    if (u == p) continue;

    int ne, it = O.size();
    while (1) {
      ne = O.front();
      if (gcd(ne, e) == 1) break;
      else {
        O.pop_front();
        O.push_back(ne);
      }
    }
    ne = O.front(); O.pop_front();
    dfs(u, v, ne);
  }
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) adj[i].clear();
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v); adj[v].push_back(u);
  }

  assert(O.empty());
  memset(V, -1, sizeof(V));
  for (int i = 1; i <= N; ++i) O.push_back(i);
  shuffle(O.begin(), O.end(), mt19937(chrono::steady_clock::now().time_since_epoch().count()));

  int ne = O.front(); O.pop_front();
  dfs(1, -1, ne);

  for (int i = 1; i <= N; ++i) cout << V[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
