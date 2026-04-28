#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int H, W, C, D; cin >> H >> W >> C >> D;

  vector<int> V(H);
  iota(V.begin(), V.end(), 0);
  for (int i = 0; i < H; ++i) D -= i;
  if (D < 0) return cout << "-1\n", void();

  int i = H - 1;
  while (D--) {
    ++V[i--];
    if (i < 0) i = H - 1;
  }

  for (int i = 0; i < H; ++i) if (V[i] > W) return cout << "-1\n", void();
  for (int i = 0; i < H; ++i) {
    int t = W;
    while (t--) {
      if (V[i]) cout << "9 ", --V[i];
      else cout << "1 ";
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
