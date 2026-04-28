#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  map<char, int> cnt;
  for (char c : S) ++cnt[c];

  int cmax = 0;
  for (auto [_, v] : cnt) cmax = max(cmax, v);

  vector<char> ans;
  if (cnt['B'] == cmax) ans.push_back('B');
  if (cnt['S'] == cmax) ans.push_back('S');
  if (cnt['A'] == cmax) ans.push_back('A');

  if (ans.size() == 3) cout << "SCU\n";
  else for (char c : ans) cout << c;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
