#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 400, INF = 1e9 + 7, PRE = -1e5;
vector<int> L, R;
int d[MAX + 1][MAX + 1][MAX + 1];
int ls, rs, N;

int rec(int l, int r, int t) {
  if (d[l][r][t] != PRE) return d[l][r][t];
  if (t == N) {
    if (l == ls && r == rs) return 0;
    else return -INF;
  }

  int res = rec(l, r, t + 1);
  if (r < rs && t - l < N - ls) res = max(res, rec(l, r + 1, t + 1));
  if (l < ls && t - r < N - rs) res = max(res, rec(l + 1, r, t + 1));
  if (l < ls && r < rs) res = max(res, rec(l + 1, r + 1, t + 1) + L[l] * R[r]);

  return d[l][r][t] = res;
}

void solve() {
  cin >> N;

  int x;
  for (int i = 1; i <= N; i++) {
    cin >> x;
    if (x == 0) continue;
    L.push_back(x);
  }
  for (int i = 1; i <= N; i++) {
    cin >> x;
    if (x == 0) continue;
    R.push_back(x);
  }

  ls = L.size(), rs = R.size();
  for (int i = 0; i <= ls; i++) for (int j = 0; j <= rs; j++) for (int k = 0; k <= N; k++) d[i][j][k] = PRE;
  cout << rec(0, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
