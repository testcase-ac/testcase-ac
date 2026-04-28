#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int p[MAX];

void solve() {
  int n, k;
  cin >> n >> k;

  priority_queue<pii> pq;
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    pq.push({p[i], -i});
  }

  while (k--) {
    auto [v, i] = pq.top();
    i = -i;
    pq.pop();

    if (v <= 100) return cout << "impossible\n", void();
    p[i] -= 100;
    pq.push({p[i], -i});
  }

  for (int i = 0; i < n; i++) cout << p[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
