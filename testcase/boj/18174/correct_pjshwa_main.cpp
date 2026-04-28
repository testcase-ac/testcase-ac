#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int R, C, K; cin >> R >> C >> K;

  int W[4]; // L, R, U, D
  W[0] = W[1] = C; W[2] = W[3] = R;
  string T[4] = {"left", "right", "top", "bottom"};

  while (K--) {
    int r, c; cin >> r >> c;
    W[0] = min(W[0], c - 1);
    W[1] = min(W[1], C - c);
    W[2] = min(W[2], r - 1);
    W[3] = min(W[3], R - r);
  }

  while (1) {
    int sum = 0;
    for (int i = 0; i < 4; ++i) sum ^= W[i];

    if (sum == 0) cout << "pass";
    else {
      for (int i = 0; i < 4; ++i) {
        int nw = W[i] ^ sum;
        if (nw <= W[i]) {
          cout << T[i] << ' ' << W[i] - nw;
          W[i] = nw;
          break;
        }
      }
    }
    cout << endl;

    string respd; cin >> respd;
    if (respd == "yuck!") break;

    int respw; cin >> respw;
    for (int i = 0; i < 4; ++i) {
      if (T[i] == respd) {
        W[i] -= respw;
        break;
      }
    }
  }
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
