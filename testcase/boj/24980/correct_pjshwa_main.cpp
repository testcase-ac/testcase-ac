#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int mode = 0, ans = 0;
  for (int i = N / 2 - 1; i >= 0; i--) {
    char a = S[2 * i], b = S[2 * i + 1];
    if (a == b) continue;
    if ((a == 'H') == (mode == 0)) continue;
    mode ^= 1; ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
