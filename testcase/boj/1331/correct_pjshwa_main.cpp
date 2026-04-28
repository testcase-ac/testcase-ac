#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 6;
bool vis[MAX][MAX];

bool valid_move(int sr, int sc, int er, int ec) {
  return (abs(sr - er) == 2 && abs(sc - ec) == 1) || (abs(sr - er) == 1 && abs(sc - ec) == 2);
}

void solve() {
  int lr, lc, sr, sc;
  for (int i = 0; i < 36; i++) {
    string S; cin >> S;
    int r = S[0] - 'A', c = S[1] - '1';

    if (vis[r][c]) return cout << "Invalid\n", void();

    if (i) {
      if (!valid_move(lr, lc, r, c)) return cout << "Invalid\n", void();
    }
    else sr = r, sc = c;

    vis[r][c] = true;
    lr = r, lc = c;
  }

  if (valid_move(lr, lc, sr, sc)) cout << "Valid\n";
  else cout << "Invalid\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
