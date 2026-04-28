#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
pair<double, int> books[MAX + 1];
ll d[MAX + 1];

void solve() {
  int n;
  cin >> n;

  ll wsum = 0;
  for (int i = 1; i <= n; i++) cin >> books[i].first;
  for (int i = 1; i <= n; i++) cin >> books[i].second, wsum += books[i].second;

  for (int i = 1; i <= n; i++) {
    auto [p, w] = books[i];
    d[i] = w;

    for (int j = 1; j < i; j++) {
      if (books[j].first > p) continue;
      d[i] = max(d[i], d[j] + w);
    }
  }

  cout << wsum - *max_element(d + 1, d + n + 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
