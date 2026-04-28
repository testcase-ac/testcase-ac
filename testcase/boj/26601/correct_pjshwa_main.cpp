#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e6 + 3;
int lp[MAX + 1], o[MAX + 1];
vector<int> pr;

void solve() {
  int N;
  cin >> N;
  if (N == 0) return cout << "1\n", void();
  if (N == 1) return cout << "2\n", void();

  o[2] = 1;
  ll ret = 2, c = 1;

  for (int p = 3;; p++) {
    map<int, int> f;
    int x = p;

    while (x > 1) {
      f[lp[x]]++;
      x /= lp[x];
    }

    bool contains = true;
    for (auto [k, v] : f) {
      if (o[k] < v) {
        contains = false;
        break;
      }
    }

    if (!contains) {
      ret = (ret * p) % MAX;
      for (auto [k, v] : f) o[k] += v;
      c++;
    }

    if (c == N) break;
  }

  cout << ret << '\n';
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

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
