#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
double d[MAX + 1][MAX + 1];
int N;
double L, R;

double r(int n, int g) {
  if (d[n][g] != -1) return d[n][g];
  if (n == 0) return g;

  double ml = r(n - 1, g + 1) - 1;
  double mm = r(n - 1, g);
  double mr = r(n - 1, max(0, g - 1)) + 1;
  return d[n][g] = L * ml + R * mr + (1 - L - R) * mm;
}

void solve() {
  cin >> N >> L >> R;
  for (int i = 0; i <= N; i++) for (int j = 0; j <= N; j++) d[i][j] = -1;
  cout << fixed << setprecision(4) << r(N, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
