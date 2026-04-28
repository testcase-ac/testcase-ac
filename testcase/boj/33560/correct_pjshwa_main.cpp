#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int rewards[5];
int tick = 0, tick_pt = 4, roll_pt = 1, score = 0;

void wrap_up() {
  if (score >= 35 && score < 65) ++rewards[1];
  if (score >= 65 && score < 95) ++rewards[2];
  if (score >= 95 && score < 125) ++rewards[3];
  if (score >= 125) ++rewards[4];

  tick = score = 0;
  tick_pt = 4;
  roll_pt = 1;
}

void solve() {
  int rolls; cin >> rolls;
  while (rolls--) {
    int d; cin >> d;
    if (tick > 240) wrap_up();

    if (d == 1) {
      wrap_up();
      continue;
    }
    if (d == 2) {
      if (roll_pt > 1) roll_pt /= 2;
      else tick_pt += 2;
    }
    if (d == 4) {
      tick += 56;
    }
    if (d == 5) {
      if (tick_pt > 1) --tick_pt;
    }
    if (d == 6) {
      if (roll_pt < 32) roll_pt *= 2;
    }

    score += roll_pt;
    tick += tick_pt;
  }

  for (int i = 1; i <= 4; ++i) cout << rewards[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
