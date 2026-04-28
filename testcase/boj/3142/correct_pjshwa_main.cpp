#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 1e6;
ll lp[MAX + 1];
bitset<MAX + 1> t;

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

  int n, fcnt = 0;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    while (x > 1) {
      if (t[lp[x]]) fcnt--;
      else fcnt++;
      t.flip(lp[x]);
      x /= lp[x];
    }

    cout << (fcnt ? "NE" : "DA") << '\n';
  }
}
