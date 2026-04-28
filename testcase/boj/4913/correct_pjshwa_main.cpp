#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MAX = 1e6;
ll lp[MAX + 1];
int p[MAX + 1], s[MAX + 1];
vector<int> pr;
int l, u;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  cout << l << ' ' << u << ' ';

  l = max(l, 1);
  u = max(u, 1);

  cout << p[u] - p[l - 1] << ' ' << s[u] - s[l - 1] << '\n';
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

  for (ll i = 2; i <= MAX; ++i) {
    p[i] = p[i - 1], s[i] = s[i - 1];
    if (lp[i] == i) {
      p[i]++;
      if (i == 2 || (i - 1) % 4 == 0) s[i]++;
    }
  }

  while (1) {
    cin >> l >> u;
    if (l == -1 && u == -1) break;
    solve();
  }
}
