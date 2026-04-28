#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  map<pair<string, string>, int> t;
  vector<pair<string, string>> v(n);
  for (int i = 0; i < n; i++) {
    string c, s;
    cin >> c >> s;
    c = c.substr(0, 2);
    if (c != s) t[{c, s}]++;
    v[i] = {c, s};
  }

  ll ans = 0;
  for (auto [c, s] : v) ans += t[{s, c}];
  cout << ans / 2 << '\n';
}
