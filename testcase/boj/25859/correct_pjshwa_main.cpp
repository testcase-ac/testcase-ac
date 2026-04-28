#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S;
  cin >> S;
  map<char, int> t;
  for (char c : S) t[c]++;

  vector<pair<char, int>> v;
  for (auto [c, cnt] : t) v.emplace_back(c, cnt);
  sort(v.begin(), v.end(), [&](auto a, auto b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
  });

  for (auto [c, cnt] : v) {
    for (int i = 0; i < cnt; i++) cout << c;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
