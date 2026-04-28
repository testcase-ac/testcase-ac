#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size(), ans = 0;
  for (int i = 2; i < N; ++i) {
    if (S[i] == 'W' && S[i - 1] == 'O' && S[i - 2] == 'W') ++ans;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
