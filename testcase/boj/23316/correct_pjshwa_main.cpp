#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50000;
ll A[MAXN], B[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  ll bsum_l = 0, bsum_r = 0;
  ll bsum_sq_l = 0, bsum_sq_r = 0;
  for (int i = 0; i < N; ++i) {
    cin >> B[i];
    bsum_r += B[i];
    bsum_sq_r += B[i] * B[i];
  }
  sort(A, A + N); sort(B, B + N);

  ll acc = 0; int bp = 0;
  for (int i = 0; i < N; ++i) {
    while (bp < N && B[bp] < A[i]) {
      bsum_l += B[bp];
      bsum_sq_l += B[bp] * B[bp];
      bsum_r -= B[bp];
      bsum_sq_r -= B[bp] * B[bp];
      ++bp;
    }

    int lc = bp, rc = N - bp;
    ll exp_l = lc * A[i] * A[i] - 2 * A[i] * bsum_l + bsum_sq_l;
    ll exp_r = rc * A[i] * A[i] - 2 * A[i] * bsum_r + bsum_sq_r;
    acc += exp_l - exp_r;
  }

  ld ans = (ld)acc / N;
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
