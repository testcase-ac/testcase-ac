#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 2e6;
ll lp[MAX + 1];

int main() {
  fast_io();

  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t;
  cin >> t;
  while (t--) {
    ll a, b;
    cin >> a >> b;
    ll s = a + b;
    if (s < 4) cout << "NO\n";
    else if (s % 2 == 0) cout << "YES\n";
    else {
      s -= 2;
      bool able = true;
      for (int p : pr) {
        if (p >= s) break;
        if (s % p == 0) {
          able = false;
          break;
        }
      }
      cout << (able ? "YES" : "NO") << '\n';
    }
  }
}
