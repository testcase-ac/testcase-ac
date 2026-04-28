#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
double P[MAX + 1]; int T;
double PP[MAX + 1], PE[MAX + 1], E[MAX + 1];

// C(n, k) / 2 ^ n
double p(int n, int k) {
  double ret = 1;
  for (int i = 1; i <= n; i++) {
    if (i <= k) {
      ret *= (n - i + 1);
      ret /= i;
    }
    ret /= 2;
  }
  return ret;
}

double dpow(double x, int n) {
  double ret = 1;
  while (n) {
    if (n & 1) ret *= x;
    x *= x;
    n >>= 1;
  }
  return ret;
}

void solve() {
  int K; cin >> T >> K;

  for (int i = 1; i <= T; i++) {
    P[i] = p(T - 1, i - 1);
    PP[i] = PP[i - 1] + P[i];
  }
  for (int i = T; i >= 1; i--) PE[i] = PE[i + 1] + i * P[i];

  E[0] = 0; int l = 0;
  while (l < K) {
    int left = 1, right = K - l + 1;
    int t = (int)E[l];

    while (left < right) {
      int mid = (left + right) / 2;

      double a = PP[t], b = PE[t + 1];
      double v = dpow(a, mid) * E[l];
      v += b * (1 - dpow(a, mid));
    }

  }

  cout << fixed << setprecision(10) << E[K] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
