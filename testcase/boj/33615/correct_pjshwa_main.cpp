#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  if (S.back() == '5') return cout << "0 5\n", void();

  int rem = 0, N = S.size(), pos1 = -1, pos5 = -1;
  for (int i = 0; i < N; ++i) {
    char c = S[i];
    rem = (rem + c - '0') % 3;
    if (c == '1') pos1 = i + 1;
    if (c == '5') pos5 = i + 1;
  }
  assert(pos1 != -1);

  if (rem == 0) cout << "0 3\n";
  else if (rem == 1) cout << pos1 << " 3\n";
  else if (rem == 2) {
    if (pos5 == -1) cout << (N & 1) << " 11\n";
    else cout << pos5 << " 3\n";
  }
  else assert(false);
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
