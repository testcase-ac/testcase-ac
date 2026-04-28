#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
int d[MAX + 1], lp[MAX + 1];
bool is_prime[MAX + 1];
vector<int> pr;
int p, e;

int mscore(int s) {
  if (s == e) return 0;
  if (d[s] != -1) return d[s];

  int mvalue = -1e9, addend = 0;
  for (int i = s + 1; i <= min(e, s + p); i++) {
    if (is_prime[i]) addend++;
    mvalue = max(mvalue, addend - mscore(i));
  }
  return d[s] = mvalue;
}

void solve() {
  cin >> p >> e;
  memset(d, -1, sizeof(d));

  int res = mscore(0);
  if (res > 0) cout << "kuro\n";
  if (res < 0) cout << "siro\n";
  if (res == 0) cout << "draw\n";
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      is_prime[i] = true;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t;
  cin >> t;
  while (t--) solve();
}
