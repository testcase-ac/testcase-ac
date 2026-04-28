#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S;
  cin >> N >> S;
  
  int ans = 0, dt = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] == '(') dt++;
    else dt--;

    ans = max(ans, abs(dt));
  }

  if (dt == 0) cout << ans << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
