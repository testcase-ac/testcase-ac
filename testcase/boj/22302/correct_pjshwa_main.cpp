#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int D[MAX + 1], T[MAX + 1], lp[MAX + 1];
vector<int> pr;

void solve() {
  int N;
  cin >> N;
  cout << D[N] << ' ' << T[N] << '\n';
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

  for (int i = 2; i <= MAX; i++) {
    D[i] = D[i - 1]; T[i] = T[i - 1];
    if (lp[i] == i) D[i]++;

    int n = i;
    for (int j = 2; j * j <= i; j++) {
      while (n % j == 0) n /= j, T[i]++;
    }
    if (n > 1) T[i]++;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
