#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_increasing(int V[4]) {
  for (int i = 1; i < 4; ++i) if (V[i - 1] >= V[i]) return false;
  return true;
}

void solve() {
  int P[2]; string S; cin >> P[0] >> P[1] >> S;

  vector<pii> candidates;
  for (int Q1 = 1; Q1 <= 9; ++Q1) for (int Q2 = Q1 + 1; Q2 <= 9; ++Q2) {
    int V[4], Q[2] = {Q1, Q2}, pi = 0, qi = 0;
    for (int i = 0; i < 4; ++i) {
      if (S[i] == 'A') V[i] = P[pi++];
      else V[i] = Q[qi++];
    }
    if (is_increasing(V)) candidates.emplace_back(Q1, Q2);
  }

  if (candidates.size() != 1) cout << "-1\n";
  else {
    auto [Q1, Q2] = candidates[0];
    cout << Q1 << ' ' << Q2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
