#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 0; string S, cur; cin >> N >> S;
  for (int i = 0; i < N; ++i) {
    if (isdigit(S[i])) cur += S[i];
    else if (cur.size() > 0) ans += stoi(cur), cur = "";
  }
  if (cur.size() > 0) ans += stoi(cur);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
