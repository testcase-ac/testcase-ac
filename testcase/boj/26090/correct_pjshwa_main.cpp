#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int lp[MAX + 1];
vector<int> pr;

int P[MAX + 1];

bool is_prime(int n) {
  if (n <= 1) return false;
  return lp[n] == n;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> P[i], P[i] += P[i - 1];

  int ans = 0;
  for (int i = 1; i <= N; i++) for (int j = i; j <= N; j++) {
    int len = j - i + 1;
    if (!is_prime(len)) continue;

    int sum = P[j] - P[i - 1];
    if (is_prime(sum)) ans++;
  }

  cout << ans << '\n';
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
