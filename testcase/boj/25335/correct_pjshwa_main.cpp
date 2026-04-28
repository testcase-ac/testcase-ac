#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, M, x, y;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> x >> y;

  int rc = 0, bc = 0, gc = 0;
  for (int i = 0; i < M; i++) {
    string C;
    cin >> x >> y >> C;
    if (C == "R") rc++;
    if (C == "B") bc++;
    if (C == "G") gc++;
  }
  if (gc & 1) rc++;

  if (rc > bc) cout << "jhnah917\n";
  else cout << "jhnan917\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
