#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
tii V[MAX + 1];
map<int, int> C[MAX + 1];
int g = 0;

void add_edge(int u, int v, int w) {
  if (C[u][w] == 0) {
    if (C[v][w] == 0) g++;
  }
  else {
    if (C[v][w] != 0) g--;
  }
  C[u][w]++; C[v][w]++;
}

void remove_edge(int u, int v, int w) {
  C[u][w]--; C[v][w]--;
  if (C[u][w] == 0) {
    if (C[v][w] == 0) g--;
  }
  else {
    if (C[v][w] != 0) g++;
  }
}

void solve() {
  int N, M, Q;
  cin >> N >> M >> Q;

  for (int i = 1; i <= N - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    V[i] = {u, v, w};
    add_edge(u, v, w);
  }

  while (Q--) {
    int p, w;
    cin >> p >> w;

    auto [u, v, o] = V[p];

    if (o != w) {
      remove_edge(u, v, o);
      add_edge(u, v, w);
      V[p] = {u, v, w};
    }

    cout << g << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
