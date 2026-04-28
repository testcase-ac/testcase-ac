#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
int cost[MAX + 1][MAX + 1];

void solve() {
  int R, N, L;
  cin >> R >> N >> L;

  vector<int> a(L);
  for (int i = 0; i < L; i++) cin >> a[i];

  map<pii, vector<int>> p2r;
  map<int, vector<int>> n2r;
  for (int i = 1; i <= R; i++) {
    int I;
    cin >> I;
    vector<int> rpts(I);
    for (int j = 0; j < I; j++) cin >> rpts[j];
    for (int j = 0; j < I; j++) {
      int u = rpts[j], v = rpts[(j + 1) % I];
      n2r[u].push_back(i);

      if (u > v) swap(u, v);
      p2r[{u, v}].push_back(i);
    }
  }

  for (int i = 1; i <= R; i++) for (int j = 1; j <= R; j++) cost[i][j] = INF;
  for (int k = 1; k <= R; k++) cost[k][k] = 0;

  for (auto& [k, v] : p2r) {
    int z = v.size();
    for (int i = 0; i < z; i++) {
      int x = v[i], y = v[(i + 1) % z];
      cost[x][y] = cost[y][x] = 1;
    }
  }

  // Floyd-warshall
  for (int k = 1; k <= R; k++) {
    for (int i = 1; i <= R; i++) {
      for (int j = 1; j <= R; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int mmove = INF, mreg = -1;
  for (int k = 1; k <= R; k++) {
    int cmove = 0;
    for (int p : a) {
      int pmove = INF;
      for (int rr : n2r[p]) pmove = min(pmove, cost[k][rr]);
      cmove += pmove;
    }

    if (cmove < mmove) {
      mmove = cmove;
      mreg = k;
    }
  }

  cout << mmove << '\n' << mreg << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
