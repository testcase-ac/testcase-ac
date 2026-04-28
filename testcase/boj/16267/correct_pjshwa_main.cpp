#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll upto(ll n) {
  if (n <= 9) return n;
  string s = to_string(n);

  ll pow = 1, res = 9;
  for (int i = 0; i < s.size() - 2; i++) {
    res += 9 * pow;
    pow *= 10;
  }
  res += pow * (s[0] - '1');

  ll addend = s.size() == 2 ? 0 : stoll(s.substr(1, s.size() - 2));
  res += addend + (s[0] <= s[s.size() - 1]);
  return res;
}

void solve() {
  ll l, r;
  cin >> l >> r;
  cout << upto(r) - upto(l - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
