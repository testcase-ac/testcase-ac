#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN + 5], P[MAXN + 5];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  while (M--) {
    int l, r; cin >> l >> r;
    ++P[l]; --P[r + 1];
  }
  for (int i = 1; i <= N; ++i) P[i] += P[i - 1];

  double ans = 0;
  for (int i = 1; i <= N; ++i) {
    if (P[i] == 0) ans += A[i];
    else {
      ll sum = 0, cnt = 0;
      for (int f = 2; f * f <= A[i]; ++f) {
        if (A[i] % f == 0) {
          sum += f; ++cnt;
          while (A[i] % f == 0) A[i] /= f;
        }
      }
      if (A[i] > 1) {
        sum += A[i]; ++cnt;
      }
      ans += (double)sum / cnt;
    }
  }

  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
