#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

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
  ll d, n;
  cin >> d >> n;

  if (d == 5) {
    vector<int> fdprimes;
    for (int i = 10000; i <= 99999; i++) {
      if (is_prime(i)) fdprimes.push_back(i);
    }

    for (int p1 : fdprimes) for (int p2 : fdprimes) {
      ll l = stoll(to_string(p1) + to_string(p2));
      if (l > n) {
        cout << l << '\n';
        return;
      }
    }
  }

  while (1) {
    string s = to_string(n);
    for (int i = d; i <= s.size(); i++) {
      string s1 = s.substr(0, i), s2 = s.substr(i);
      if (s2.size() < d) continue;
      if (s2[0] == '0') continue;

      if (is_prime(stoll(s1)) && is_prime(stoll(s2))) {
        cout << n << '\n';
        return;
      }
    }
    n++;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
