#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e7, MOD = 1e9 + 7;
ll lp[MAX + 1];
vector<int> pr;
vector<pair<ll, ll>> mile;

int tc;
void solve() {
  cout << "Case " << ++tc << ": ";

  ll N;
  cin >> N;

  auto it = upper_bound(mile.begin(), mile.end(), make_pair(N, (ll)1e14));
  if (it == mile.begin()) cout << "1\n";
  else {
    it--;
    cout << it->second << '\n';
  }
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  for (int p : pr) {
    __int128_t z = 0, c = 1;
    while (c * p <= 1e14) {
      c *= p;
      z++;
      if (z > 1) mile.push_back({c, p});
    }
  }
  sort(mile.begin(), mile.end());

  ll prev = 1;
  for (auto& [u, p] : mile) {
    p = (prev * p) % MOD;
    prev = p;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
