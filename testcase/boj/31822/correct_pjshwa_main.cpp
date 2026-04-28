#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string O; cin >> O;

  int N, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    ans += (O.substr(0, 5) == S.substr(0, 5));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
