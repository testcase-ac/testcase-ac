#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int cdist[MAX + 1];

void solve() {
  int N, a, b; cin >> N >> a >> b;
  a++, b++;

  int dv[3] = {-1, -a, -b};

  queue<int> q;
  q.push(N);
  cdist[N] = 0;

  while (!q.empty()) {
    int v = q.front(); q.pop();

    if (v == 0) {
      cout << cdist[v] << '\n';
      return;
    }

    for (int k = 0; k < 3; k++) {
      int nv = v + dv[k];
      if (nv < 0) continue;
      if (cdist[nv]) continue;
      cdist[nv] = cdist[v] + 1;
      q.push(nv);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
