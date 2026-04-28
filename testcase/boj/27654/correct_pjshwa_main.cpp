#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
const double EPS = 1e-7;
int v[MAX], w[MAX];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> v[i] >> w[i];

  double left = 0, right = 1e6 + 1;
  while (left + EPS < right) {
    double mid = (left + right) / 2;

    priority_queue<double> pq;
    for (int i = 0; i < n; i++) pq.push(v[i] - mid * w[i]);

    double res = 0;
    for (int i = 0; i < k; i++) res += pq.top(), pq.pop();

    if (res >= 0) left = mid + EPS;
    else right = mid;
  }

  priority_queue<pair<double, int>> pq;
  for (int i = 0; i < n; i++) pq.push({v[i] - left * w[i], i});

  ll vsum = 0, wsum = 0;
  for (int i = 0; i < k; i++) {
    auto [_, idx] = pq.top(); pq.pop();
    vsum += v[idx], wsum += w[idx];
  }
  cout << fixed << setprecision(10) << (double)vsum / wsum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
