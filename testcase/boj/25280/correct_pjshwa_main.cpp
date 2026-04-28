#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const double EPS = 1e-7;

void solve() {
  int N;
  cin >> N;
  vector<pair<double, double>> a(N);
  for (int i = 0; i < N; i++) cin >> a[i].first >> a[i].second;

  double left = 0, right = 1e5 + 1;
  while (left + EPS < right) {
    double mid = (left + right) / 2;

    double cprob = 1;
    for (int i = 0; i < N; i++) {
      auto [s, e] = a[i];
      if (mid >= e) {
        cprob = 0;
        break;
      }
      else if (mid <= s) continue;
      else cprob *= (e - mid) / (e - s);
    }

    if (cprob >= 0.5) left = mid + EPS;
    else right = mid;
  }

  cout << fixed << setprecision(10) << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
