#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S, T; cin >> N >> S >> T;
  reverse(T.begin(), T.end());

  int l = 0;
  for (int i = 0; i < N; ++i) {
    string ss = S.substr(l, i - l + 1), tt = T.substr(l, i - l + 1);
    reverse(ss.begin(), ss.end());
    if (ss == tt) l = i + 1;
  }

  cout << (l == N ? "Yes" : "No") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
