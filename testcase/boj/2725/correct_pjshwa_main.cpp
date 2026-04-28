#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MAX = 1e3;
ll lp[MAX + 1], phi[MAX + 1];
ll phipf[MAX + 1];

int main() {
  vector<int> pr;
  phi[1] = 1;

  // Sieve of Eratosthenes O(n)
  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      phi[i] = i - 1;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++) {
      lp[i * pr[j]] = pr[j];
      if (i % pr[j]) phi[i * pr[j]] = phi[i] * phi[pr[j]];
      else phi[i * pr[j]] = phi[i] * pr[j];
    }
  }

  for (ll i = 1; i <= MAX; ++i) phipf[i] = phipf[i - 1] + phi[i];

  int t, n;
  cin >> t;

  while (t--) {
    cin >> n;
    cout << 2 * phipf[n] + 1 << '\n';
  }
}
