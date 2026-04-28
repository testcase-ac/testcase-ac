#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;

  int N = S.size(); ll ans = 0;
  for (int i = 0; i < N; i++) {
    string R = "";
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      R += S[j];
    }
    sort(R.begin(), R.end(), greater<>());
    ans = max(ans, stoll(R) + stoll(S.substr(i, 1)));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
