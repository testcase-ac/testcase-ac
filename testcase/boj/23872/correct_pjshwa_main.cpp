#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 1e5, INF = 1e18;
ll X[MAX], Y[MAX], E[MAX];
ll d[MAX][2], sum;
int N, K;

// Current index, must pair
ll rec(int i, int p) {
  if (i >= N - 1) return 0;
  if (d[i][p] != -1) return d[i][p];

  ll ret = INF;
  if (!p) {
    if (X[i + 1] - X[i] > K) ret = min(ret, rec(i + 1, 0));
    else ret = min(ret, rec(i + 1, 1));
  }

  if (i + 1 < N && X[i + 1] - X[i] <= K) {
    ret = min(ret, rec(i + 2, 0) + Y[i] + Y[i + 1]);
  }
  if (i + 2 < N && X[i + 2] - X[i] <= K) {
    ret = min(ret, rec(i + 3, 0) + Y[i] + Y[i + 2]);
  }

  return d[i][p] = ret;
}

void solve_T1() {
  ll streak = 0, mval = INF, lx = -INF, ans = 0;
  for (int i = 0; i < N; i++) {
    if (X[i] - lx > K) {
      if (streak & 1) ans += mval;
      streak = 1, mval = INF;
    }
    else streak++;

    if (streak & 1) mval = min(mval, Y[i]);
    lx = X[i];
  }
  if (streak & 1) ans += mval;

  cout << ans << '\n';
}

void solve_T2() {
  sum = accumulate(Y, Y + N, 0LL);

  int r = 0;
  for (int l = 0; l < N; l++) {
    r = max(r, l);
    while (r < N - 1 && X[r + 1] - X[r] <= K) r++;
    E[l] = r;
  }

  memset(d, -1, sizeof(d));
  cout << sum - rec(0, 0) << '\n';
}

void solve() {
  int T; cin >> T >> N >> K;
  for (int i = 0; i < N; i++) cin >> X[i] >> Y[i];

  if (T == 1) solve_T1();
  if (T == 2) solve_T2();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
