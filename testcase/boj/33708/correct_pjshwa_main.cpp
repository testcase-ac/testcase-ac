#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, MAXV = 1e6;
int A[MAXN + 1], lp[MAXV + 1], C[MAXN + 1];
vector<int> pr;

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) {
    int x = A[i];
    while (x > 1) {
      int p = lp[x];
      while (x % p == 0) x /= p, ++C[i];
    }
    if (C[i] > 1) return cout << "YES\n", void();
  }

  for (int i = 1; i < N; ++i) {
    if (C[i] == 1 && C[i - 1] == 1) return cout << "YES\n", void();
  }
  for (int i = 1; i < N; ++i) {
    if (A[i] < A[i - 1]) return cout << "NO\n", void();
  }
  cout << "YES\n";
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXV; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXV; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
