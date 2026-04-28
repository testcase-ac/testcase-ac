#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Fraction {
  ll n, d;

  bool operator<(const Fraction &f) const {
    return n * f.d > d * f.n;
  }
};

void solve() {
  int m, k;
  cin >> m >> k;

  priority_queue<Fraction> pq;
  for (int i = 2; i <= m; i++) pq.push({1, i});

  while (--k && !pq.empty()) {
    auto [n, d] = pq.top();
    pq.pop();

    n++;
    while (n < d && __gcd(n, d) > 1) n++;
    if (n < d) pq.push({n, d});
  }

  if (pq.empty()) cout << "-1\n";
  else cout << pq.top().n << ' ' << pq.top().d << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
