#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 8e6;
int cdist[MAX + 1];

void solve() {
  int n; cin >> n;
  cout << cdist[n] << '\n';
}

int main() {
  fast_io();

  queue<int> q;
  memset(cdist, 0x3f, sizeof(cdist));
  cdist[1] = 0; q.push(1);

  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (int u : {2 * v, v - 1}) {
      if (u < 0 || u > MAX) continue;
      if (cdist[u] > cdist[v] + 1) {
        cdist[u] = cdist[v] + 1;
        q.push(u);
      }
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
