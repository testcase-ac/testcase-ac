#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
using T = tuple<double, double, double>;
T dp[MAXN + 1][MAXN + 1][MAXN + 1];
T def = {-1, -1, -1};

T rec(int r, int y, int b) {
  if (r == 0) return {0, 1, 0};
  if (y == 0) return {0, 0, 1};
  if (b == 0) return {1, 0, 0};
  if (dp[r][y][b] != def) return dp[r][y][b];

  double cr = 0, cy = 0, cb = 0;
  int tot = r * y + y * b + b * r;
  {
    auto [nr, ny, nb] = rec(r, y - 1, b);
    double p = (double)(r * y) / tot;
    cr += nr * p; cy += ny * p; cb += nb * p;
  }
  {
    auto [nr, ny, nb] = rec(r, y, b - 1);
    double p = (double)(y * b) / tot;
    cr += nr * p; cy += ny * p; cb += nb * p;
  }
  {
    auto [nr, ny, nb] = rec(r - 1, y, b);
    double p = (double)(b * r) / tot;
    cr += nr * p; cy += ny * p; cb += nb * p;
  }

  return dp[r][y][b] = {cr, cy, cb};
}

void solve() {
  int R, Y, B; cin >> R >> Y >> B;

  auto [pr, py, pb] = rec(R, Y, B);
  cout << fixed << setprecision(12) << pr << ' ' << py << ' ' << pb << '\n';
}

int main() {
  fast_io();

  for (int r = 0; r <= MAXN; ++r) for (int y = 0; y <= MAXN; ++y) for (int b = 0; b <= MAXN; ++b) {
    dp[r][y][b] = def;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
