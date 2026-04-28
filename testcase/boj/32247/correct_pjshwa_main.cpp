#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int C[MAXN + 1], H[MAXN + 1];

void fail() {
  cout << "adios\n";
  exit(0);
}

void solve() {
  int N, M; cin >> N >> M;

  memset(C, -1, sizeof(C));
  for (int i = 0; i < M; ++i) {
    int c, x, h; cin >> c >> x >> h;
    C[x] = c; H[x] = h;
  }

  int cy = 0;
  for (int i = 1; i <= N; ++i) {
    int c = C[i], h = H[i];
    if (c == -1) --cy;
    else if (c == 0) cy = max(cy - 1, h + 1);
    else {
      --cy;
      if (cy >= h) fail();
    }
  }

  if (cy > 0) fail();
  cout << "stay\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
