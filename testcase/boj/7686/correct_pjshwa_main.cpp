#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int n, k, v[MAX], w[MAX];

void solve() {
  for (int i = 0; i < n; ++i) cin >> v[i];
  for (int i = 0; i < n; ++i) cin >> w[i];
  k = n - k;

  double left = 0, right = 1e9 + 1;
  for (int t = 0; t < 100; ++t) {
    double mid = (left + right) / 2;

    priority_queue<double> pq;
    for (int i = 0; i < n; i++) pq.push(v[i] - mid * w[i]);

    double res = 0;
    for (int i = 0; i < k; i++) res += pq.top(), pq.pop();

    if (res >= 0) left = mid;
    else right = mid;
  }

  priority_queue<pair<double, int>> pq;
  for (int i = 0; i < n; i++) pq.push({v[i] - left * w[i], i});

  ll vsum = 0, wsum = 0;
  for (int i = 0; i < k; i++) {
    int idx = pq.top().second; pq.pop();
    vsum += v[idx], wsum += w[idx];
  }

  int ans = round(100 * (double)vsum / wsum);
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> n >> k) {
    if (n == 0 && k == 0) break;
    solve();
  }
}
