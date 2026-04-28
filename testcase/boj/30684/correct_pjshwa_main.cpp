#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  string ans = "ZZZ";
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    if (S.size() != 3) continue;
    ans = min(ans, S);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
