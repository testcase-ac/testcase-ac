#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_palindrome_number(ll n) {
  string s = to_string(n);
  int len = s.size();
  for (int i = 0; i < len / 2; i++) {
    if (s[i] != s[len - i - 1]) return false;
  }
  return true;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll n;
  cin >> n;

  int ans = 0;
  for (ll i = 1; i * i <= n; i++) {
    if (n % i) continue;

    if (is_palindrome_number(i)) ans++;
    if (i != n / i && is_palindrome_number(n / i)) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
