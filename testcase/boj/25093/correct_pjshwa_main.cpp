#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  string s;
  cin >> s;

  vector<pair<char, int>> v;
  char lchar = s[0];
  int streak = 1;
  for (int i = 1; i < s.size(); i++) {
    if (s[i] == lchar) streak++;
    else {
      v.push_back({lchar, streak});
      lchar = s[i];
      streak = 1;
    }
  }
  v.push_back({lchar, streak});

  string ans = "";
  for (int i = 0; i < v.size() - 1; i++) {
    auto [c1, v1] = v[i];
    auto [c2, v2] = v[i + 1];

    if (c1 < c2) v1 *= 2;
    for (int j = 0; j < v1; j++) ans += c1;
  }

  auto [c1, v1] = v.back();
  for (int j = 0; j < v1; j++) ans += c1;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
