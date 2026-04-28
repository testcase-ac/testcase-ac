#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, Q; cin >> N >> Q;
  int W = min(N, Q);

  queue<int> r_white, r_black, c_white, c_black;
  for (int i = 1; i <= W; ++i) {
    r_white.push(i);
    c_white.push(i);
  }

  vector<ll> seq(Q + 1);
  vector<pair<char, int>> ops;
  int rzw = N, rzb = 0, czw = N, czb = 0;
  for (int i = 1; i <= Q; ++i) {
    cin >> seq[i];
    ll dif = seq[i] - seq[i - 1];
    if (dif == rzw - rzb && !c_white.empty()) {
      int f = c_white.front(); c_white.pop();
      c_black.push(f);
      --czw, ++czb;
      ops.emplace_back('C', f);
    }
    else if (dif == rzb - rzw && !c_black.empty()) {
      int f = c_black.front(); c_black.pop();
      c_white.push(f);
      ++czw, --czb;
      ops.emplace_back('C', f);
    }
    else if (dif == czw - czb && !r_white.empty()) {
      int f = r_white.front(); r_white.pop();
      r_black.push(f);
      --rzw, ++rzb;
      ops.emplace_back('R', f);
    }
    else if (dif == czb - czw && !r_black.empty()) {
      int f = r_black.front(); r_black.pop();
      r_white.push(f);
      ++rzw, --rzb;
      ops.emplace_back('R', f);
    }
    else return cout << "-1\n", void();
  }

  for (auto& [c, i] : ops) cout << c << ' ' << N + 1 - i << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
