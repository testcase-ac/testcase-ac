#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
double X[MAXN + 1], Y[MAXN + 1];

double dist(int i, int j) {
  return sqrt((X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]));
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];
  cout << fixed << setprecision(10) << dist(0, N - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
