#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int C[6]{};
  for (char c : S) {
    if (c == 's') ++C[0];
    if (c == 'o' && C[0]) --C[0], ++C[1];
    if (c == 'g') {
      if (C[4]) --C[4], ++C[5];
      else if (C[1]) --C[1], ++C[2];
    }
    if (c == 'a' && C[2]) --C[2], ++C[3];
    if (c == 'n' && C[3]) --C[3], ++C[4];
  }

  cout << C[5] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
