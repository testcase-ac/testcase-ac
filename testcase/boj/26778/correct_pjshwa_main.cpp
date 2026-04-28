#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size(), streak = 1, ans = 0;
  for (int i = 1; i < N; i++) {
    if (S[i] == S[i - 1]) streak++;
    else ans += streak - 1, streak = 1;
  }
  ans += streak - 1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
