#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s, t;
  cin >> s >> t;

  bool neg = false;
  if (s[0] == '-') neg ^= 1, s = s.substr(1);
  if (t[0] == '-') neg ^= 1, t = t.substr(1);

  s = s[0] + s.substr(2);
  t = t[0] + t.substr(2);
  __int128_t u = stoll(s);
  u *= stoll(t);

  stack<int> r;
  while (u) r.push(u % 10), u /= 10;
  while (r.size() < 19) r.push(0);

  if (neg) cout << '-';
  while (!r.empty()) {
    cout << r.top();
    if (r.size() == 19) cout << '.';
    r.pop();
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
