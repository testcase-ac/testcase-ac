#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (ll i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  string s;
  cin >> s;
  for (char& c : s) {
    if (c == '3' || c == '4' || c == '7') return cout << "no\n", void();
  }

  if (!is_prime(stoll(s))) return cout << "no\n", void();
  string t = "";
  reverse(s.begin(), s.end());
  for (char& c : s) {
    if (c == '6') t += '9';
    else if (c == '9') t += '6';
    else t += c;
  }
  if (!is_prime(stoll(t))) return cout << "no\n", void();
  cout << "yes\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
