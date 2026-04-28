#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int ans = 0;

  string S; cin >> S;
  for (char c : S) {
    if (ans % 5 == 0 && c == 'K') ans++;
    else if (ans % 5 == 1 && c == 'O') ans++;
    else if (ans % 5 == 2 && c == 'R') ans++;
    else if (ans % 5 == 3 && c == 'E') ans++;
    else if (ans % 5 == 4 && c == 'A') ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
