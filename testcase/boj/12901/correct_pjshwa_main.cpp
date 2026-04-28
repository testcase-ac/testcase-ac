#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int parent[MAX + 1];
int lp[MAX + 1];
vector<int> pr;

int Find(int x) {
  if (x != parent[x]) parent[x] = Find(parent[x]);
  return parent[x];
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  ll A, B, P; cin >> A >> B >> P;

  ll N = B - A;
  iota(parent, parent + N + 1, 0);

  for (int p : pr) {
    if (p < P) continue;

    ll g = (p - A % p) % p;
    for (int i = g; i <= N; i += p) Union(g, i);
  }

  set<int> U;
  for (int i = 0; i <= N; ++i) U.insert(Find(i));
  cout << U.size() << '\n';
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
