#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int cdist[MAX + 1];

void solve() {
  int N, S, E; cin >> N >> S >> E;

  memset(cdist, 0x3f, sizeof(cdist));
  queue<int> q; q.push(S); cdist[S] = 0;
  while (!q.empty()) {
    int v = q.front(); q.pop();

    // Riffle
    int nv1 = v > N ? 2 * (v - N) : 2 * v - 1;

    // Scuffle
    int nv2 = v % 2 ? v + 1 : v - 1;

    for (int nv : {nv1, nv2}) {
      if (nv < 1 || nv > 2 * N) continue;
      if (cdist[nv] <= cdist[v] + 1) continue;
      cdist[nv] = cdist[v] + 1;
      q.push(nv);
    }
  }

  cout << cdist[E] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
