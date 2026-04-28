#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string T;
  cin >> T;
  string S = T;
  sort(S.begin(), S.end());

  vector<pii> ans;
  for (int i = 0; i < S.size(); i++) {
    if (S[i] == T[i]) continue;

    for (int j = i + 1; j < S.size(); j++) {
      if (S[j] != T[i]) continue;

      swap(S[i], S[j]);
      if (S[i] > S[j]) ans.push_back({j, i});
      else ans.push_back({i, j});
      break;
    }
  }

  for (auto& [i, j] : ans) cout << i + 1 << ' ' << j + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
 