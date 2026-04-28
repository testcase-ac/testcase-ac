#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 512;
int X[MAX], Y[MAX];
double d[MAX][MAX]; int N;

double D(int xi, int yi, int xj, int yj) {
  return sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj));
}

double r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];
  if (i == N - 1 || j == N - 1) return d[i][j] = D(X[i], Y[i], X[j], Y[j]);

  int x = max(i, j) + 1;
  double ret = min(r(x, j) + D(X[i], Y[i], X[x], Y[x]),
                  r(i, x) + D(X[j], Y[j], X[x], Y[x]));

  return d[i][j] = ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
    for (int j = 0; j < N; j++) d[i][j] = -1;
  }
  cout << r(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
