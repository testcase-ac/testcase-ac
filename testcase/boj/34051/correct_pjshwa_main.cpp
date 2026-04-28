#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;
  char maxc = S.back(); int lasti = N - 1;
  for (int i = N - 2; i >= 0; --i) {
    if (S[i] < maxc) lasti = i;
    maxc = max(maxc, S[i]);
  }

  string ans = S;
  for (int i = lasti + 1; i < N; ++i) {
    reverse(S.begin() + lasti, S.begin() + i + 1);
    if (S > ans) ans = S;
    reverse(S.begin() + lasti, S.begin() + i + 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
