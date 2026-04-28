#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int lp[MAX + 1], parent[MAX + 1];
vector<int> pr;

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

int tc;

void solve() {
  ll a, b, p;
  cin >> a >> b >> p;
  for (int i = 0; i <= b - a; i++) parent[i] = i;

  for (int prime : pr) {
    if (prime < p) continue;

    ll s = a + (prime - a % prime) % prime;
    for (ll i = s; i <= b; i += prime) Union(s - a, i - a);
  }

  set<int> distinct;
  for (int i = 0; i <= b - a; i++) distinct.insert(Find(i));
  cout << "Case #" << ++tc << ": " << distinct.size() << '\n';
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
  cin >> t;
  while (t--) solve();
}
