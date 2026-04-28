#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int lp[MAXN + 1];
vector<int> pr;

bool is_prime(int n) {
  if (n < 2) return false;
  return lp[n] == n;
}

void solve() {
  int N; cin >> N;
  int expected = N / 2;

  vector<pii> pairs;
  while (N > 6) {
    int u = N;
    while (!(is_prime(u) && 3 * u < 2 * N)) --u;

    int b = 3 * u - N;
    assert((b % 2) != (N % 2));
    for (int i = 0;; ++i) {
      int l = b + i, r = N - i;
      if (l >= r) break;
      pairs.push_back({l, r});
    }
    N = b - 1;
  }

  if (N == 3) pairs.push_back({1, 3});
  else if (N == 4 || N == 5) {
    pairs.push_back({1, 3});
    pairs.push_back({2, 4});
  }
  else if (N == 6) {
    pairs.push_back({1, 5});
    pairs.push_back({2, 4});
    pairs.push_back({3, 6});
  }

  cout << pairs.size() << '\n';
  for (auto& [a, b] : pairs) cout << a << ' ' << b << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXN; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXN; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
