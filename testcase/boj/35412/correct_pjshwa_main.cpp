#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;
  vector<char> P;
  for (auto& c : S) {
    if (!P.empty() && P.back() == c) P.pop_back();
    else if (P.size() >= 2 && P[P.size() - 2] == c) P.pop_back(), P.pop_back();
    else P.push_back(c);
  }
  string ans(P.begin(), P.end());
  if (ans.empty()) ans = "-1";
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
