#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6, INF = 0x3f3f3f3f;
int dmin[MAX + 1], dmax[MAX + 1];

void solve() {
  int N; cin >> N;
  cout << dmin[N] << ' ' << dmax[N] << '\n';
}

int main() {
  fast_io();

  fill(dmin, dmin + MAX + 1, INF);
  dmin[0] = 0;

  for (int a = 2, b = 1; a <= MAX;) {
    for (int v = a; v <= MAX; v++) {
      dmax[v] = max(dmax[v], dmax[v - a] + b);
      dmin[v] = min(dmin[v], dmin[v - a] + b);
    }
    int c = a + b; b = a; a = c;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
