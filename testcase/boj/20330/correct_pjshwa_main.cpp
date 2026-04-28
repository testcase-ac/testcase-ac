#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_palindrome(string s) {
  int n = s.size();
  for (int i = 0; i < n / 2; i++) {
    if (s[i] != s[n - i - 1]) return false;
  }
  return true;
}

vector<ll> ans;
void r(ll n) {
  string s = to_string(n);
  int sz = s.size();

  if (is_palindrome(s)) {
    ans.push_back(n);
    return;
  }

  ll u = 1;
  for (int i = 0; i < 18; i++) {
    if (n == u) {
      ans.push_back(1);
      ans.push_back(n - 1);
      return;
    }
    u *= 10;
  }

  string f = s.substr(0, sz / 2);
  string fr = f;
  reverse(fr.begin(), fr.end());
  
  string c;
  if (sz & 1) c = f + "0" + fr;
  else c = f + fr;

  if (stoll(c) > n) {
    f = to_string(stoll(f) - 1);
    fr = f;
    reverse(fr.begin(), fr.end());

    if (sz & 1) c = f + "0" + fr;
    else c = f + fr;
  }

  ans.push_back(stoll(c));
  r(n - stoll(c));
}

void solve() {
  ll n;
  cin >> n;
  r(n);

  cout << ans.size() << '\n';
  for (auto a : ans) cout << a << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
