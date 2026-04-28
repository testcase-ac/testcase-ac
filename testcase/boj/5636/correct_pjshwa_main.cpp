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

string s;
void solve() {
  int n = s.size();

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 6; j++) {
      int ss = stoi(s.substr(i, j + 1));
      if (ss < 1e5 && is_prime(ss)) ans = max(ans, ss);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> s;
    if (s == "0") break;
    solve();
  }
}
