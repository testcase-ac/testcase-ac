#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 400, INF = 1e18;
ll A[MAX], d[MAX][MAX][3], D;

ll val(ll x) {
  x = (x + D) % D;
  return min(x, D - x);
}

ll r(int i, int j, int o) {
  if (d[i][j][o] != -1) return d[i][j][o];

  ll add = 0;
  if (o == 0) add = -A[i - 1];
  if (o == 1) add = -A[j + 1];

  if (i == j) return d[i][j][o] = val(A[i] + add);

  ll ret = INF;
  ret = min(ret, r(i + 1, j, 0) + val(A[i] + add));
  ret = min(ret, r(i, j - 1, 1) + val(A[j] + add));
  return d[i][j][o] = ret;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N >> D;
  for (int i = 0; i < N; i++) cin >> A[i];

  memset(d, -1, sizeof(d));
  cout << r(0, N - 1, 2) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
