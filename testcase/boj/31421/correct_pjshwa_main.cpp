#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  vector<int> ans;
  for (int i = 0; i < N - 1; ++i) {
    if (S[i] != S[i + 1]) ans.push_back(i + 1);
  }

  int Z = ans.size();
  if (S.back() == 'B') {
    if (Z < 2) return cout << "-1\n", void();
    swap(ans[Z - 1], ans[Z - 2]);
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
