#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, k;
  cin >> n >> k;

  string s;
  int p;

  ll sv = 0;
  cin >> s >> p;
  for (int i = 0; i < s.size() - 1; i++) {
    if (s[i] == '(' && s[i + 1] == ')') sv++;
  }
  sv *= p;
  if (s[0] == ')' && s[s.size() - 1] == '(') sv += (p - 1);

  ll dv = 0;
  cin >> s >> p;
  for (int i = 0; i < s.size() - 1; i++) {
    if (s[i] == '(' && s[i + 1] == ')') dv++;
  }
  dv *= p;
  if (s[0] == ')' && s[s.size() - 1] == '(') dv += (p - 1);

  if (sv < k) cout << "0\n";
  else if (dv >= k) cout << n << '\n';
  else {
    ll left = 0, right = n;
    while (left < right) {
      __int128_t mid = (left + right) / 2;
      __int128_t val = sv - mid * (k - dv);
      if (val >= k) left = mid + 1;
      else right = mid;
    }
    cout << left << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
