#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 50'010;
int Lt[MAXV + 1], Ut[MAXV + 1];

void solve() {
  int n, m; cin >> n >> m;
  
  vector<int> L(2 * n + 1), U(2 * m + 1);
  for (int i = 0; i < 2 * n + 1; ++i) cin >> L[i];
  for (int i = 0; i < 2 * m + 1; ++i) cin >> U[i];

  for (int i = 1; i < 2 * n + 1; i += 2) {
    int yc = L[i + 1], yp = L[i - 1];
    Lt[L[i]] = yc - yp;
  }
  for (int i = 1; i < 2 * m + 1; i += 2) {
    int yc = U[i + 1], yp = U[i - 1];
    Ut[U[i]] = yc - yp;
  }

  vector<int> Lp, Up;
  int Ly = L[0], Uy = U[0];
  Lp.push_back(Ly), Up.push_back(Uy);

  for (int x = 0; x <= MAXV; ++x) {
    Ly += Lt[x], Uy += Ut[x];
    Lp.push_back(Ly), Up.push_back(Uy);
  }

  int dif = Up[0] - Lp[0], f = 1;
  ll area_cnt = 0, area_sum = 0;
  for (int x = 1; x < Lp.size(); ++x) {
    if (dif > 0 && f == 0) area_sum += dif;

    int ndif = Up[x] - Lp[x];
    if (dif <= 0 && ndif > 0) ++area_cnt, f = 0;
    dif = ndif;
  }
  if (dif > 0 && f == 0) area_sum += dif;

  if (dif > 0 && f == 0) {
    --area_cnt; int sx;
    for (int x = Lp.size() - 1; x >= 0; --x) {
      if (Up[x] - Lp[x] <= 0) {
        sx = x;
        break;
      }
    }

    for (int x = sx + 1; x < Lp.size(); ++x) {
      area_sum -= Up[x] - Lp[x];
    }
  }

  cout << area_cnt << ' ' << area_sum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
