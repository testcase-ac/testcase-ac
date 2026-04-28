#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S;
  cin >> S;
  map<char, int> t;
  for (char c : S) t[c]++;

  vector<int> U;
  for (auto [_, u] : t) U.push_back(u);
  sort(U.begin(), U.end());
  reverse(U.begin(), U.end());

  int ans = 0;
  for (int i = 2; i < U.size(); i++) ans += U[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
