#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_alpha(char c) {
  return 'a' <= c && c <= 'z';
}

void solve() {
  int N; cin >> N;

  cin.ignore();
  string S; getline(cin, S);

  map<char, int> cnt;
  for (char c : S) {
    if (is_alpha(c)) ++cnt[c];
  }

  int cmax = 0;
  for (auto [_, v] : cnt) cmax = max(cmax, v);

  cout << cmax << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
