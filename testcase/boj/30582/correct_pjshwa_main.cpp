#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXD = 50, MAXR = 2500, MOD = 1e9 + 7;
int dp1[MAXD][MAXR + 1], dp2[MAXD][MAXR + 1];
int D, R;

int rec1(int i, int p) {
  if (i == D) return 1;
  if (dp1[i][p] != -1) return dp1[i][p];

  int q = sqrt(p) + 3, ret = 0;
  for (int v = -q; v <= q; ++v) {
    int np = p - v * v;
    if (np < 0) continue;
    ret = (ret + rec1(i + 1, np)) % MOD;
  }
  return dp1[i][p] = ret;
}

int rec2(int i, int p) {
  if (i == D) return 0;
  if (dp2[i][p] != -1) return dp2[i][p];

  int q = sqrt(p) + 3, ret = 0;
  for (int v = -q; v <= q; ++v) {
    int np = p - v * v;
    if (np < 0) continue;
    ll add = rec1(i + 1, np);
    add = (add * abs(v)) % MOD;
    add = (add + rec2(i + 1, np)) % MOD;
    ret = (ret + add) % MOD;
  }
  return dp2[i][p] = ret;
}

void solve() {
  cin >> D >> R;
  memset(dp1, -1, sizeof(dp1));
  memset(dp2, -1, sizeof(dp2));
  cout << rec2(0, R * R) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
