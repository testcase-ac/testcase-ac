#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size(), i = 0;
  for (int u = 1;; u++) {
    for (char c : to_string(u)) {
      if (i < N && c == S[i]) i++;
    }
    if (i == N) {
      cout << u << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
