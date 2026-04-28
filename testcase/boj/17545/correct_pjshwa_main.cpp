#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

double d[101];
int K;

double r(int n) {
  if (n == 0) return 0;
  if (d[n] != 0) return d[n];

  double p = r(n - 1), res = 0;
  for (int i = 1; i <= K; i++) {
    res += max(p, (double)i) / K;
  }
  return d[n] = res;
}

void solve() {
  int N;
  cin >> K >> N;
  cout << fixed << setprecision(10) << r(N) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
