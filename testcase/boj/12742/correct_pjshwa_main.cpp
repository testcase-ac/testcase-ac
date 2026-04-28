#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
double GA[MAX + 1], GB[MAX + 1], W[MAX + 1];
int N, X, Y;

double f(double ause) {
  double buse = 1e9;
  for (int i = 1; i <= N; i++) buse = min(buse, (W[i] - GA[i] * ause) / GB[i]);
  return ause * X + buse * Y;
}

void solve() {
  cin >> N >> X >> Y;
  for (int i = 1; i <= N; i++) cin >> GA[i];
  for (int i = 1; i <= N; i++) cin >> GB[i];
  for (int i = 1; i <= N; i++) cin >> W[i];

  double amax = 1e9;
  for (int i = 1; i <= N; i++) amax = min(amax, W[i] / GA[i]);

  // Ternary search
  double left = 0, right = amax;
  for (int i = 0; i < 100; i++) {
    double mid1 = left + (right - left) / 3;
    double mid2 = right - (right - left) / 3;

    if (f(mid1) > f(mid2)) right = mid2;
    else left = mid1;
  }

  double ause = left, buse = 1e9;
  for (int i = 1; i <= N; i++) buse = min(buse, (W[i] - GA[i] * ause) / GB[i]);
  cout << fixed << setprecision(2) << ause * X + buse * Y << '\n' << ause << ' ' << buse << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
