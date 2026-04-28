#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S, T; cin >> N >> S >> T;

  int l = S[0] == T[0], streak = 1;
  vector<int> D;
  for (int i = 1; i < N; i++) {
    int c = S[i] == T[i];
    if (c == l) streak++;
    else {
      D.push_back(streak);
      streak = 1;
      l = c;
    }
  }
  D.push_back(streak);

  int ans = D.size() - 1;
  if (ans == 0 && S[0] != T[0]) ans = 1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
