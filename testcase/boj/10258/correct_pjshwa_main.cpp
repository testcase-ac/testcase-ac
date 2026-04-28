#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  bool f = true; int ans = 0;
  for (int i = 0; i < N; ++i) {
    char c = S[i];
    if (c == '0') continue;

    int val = (1 << (N - i)) - 1;
    if (f) ans += val;
    else ans -= val;
    f = !f;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
