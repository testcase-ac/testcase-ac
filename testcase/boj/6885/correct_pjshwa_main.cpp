#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e4, INF = 0x3f3f3f3f;
pii A[MAX + 1];
int N;
int d[MAX + 1][2];

int r(int i, int o) {
  if (i == N) {
    auto [l, r] = A[i];
    if (o) return N - l + (r - l);
    else return N - l;
  }
  if (d[i][o] != -1) return d[i][o];

  auto [cl, cr] = A[i];
  auto [nl, nr] = A[i + 1];
  int cv = o ? cl : cr, cd = cr - cl;

  int res = INF;
  res = min(res, r(i + 1, 0) + abs(cv - nl) + 1 + cd);
  res = min(res, r(i + 1, 1) + abs(cv - nr) + 1 + cd);
  return d[i][o] = res;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) {
    int x, y;
    cin >> x >> y;
    A[i] = {x, y};
  }
  if (N == 1) return cout << "0\n", void();

  memset(d, -1, sizeof(d));
  auto [cl, cr] = A[1];
  auto [nl, nr] = A[2];

  int ans = r(2, 0) + abs(cr - nl) + cr;
  ans = min(ans, r(2, 1) + abs(cr - nr) + cr);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
