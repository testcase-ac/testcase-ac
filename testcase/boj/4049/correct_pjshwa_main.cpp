#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, MAXV = 65536;
int A[MAXN][MAXN], U[MAXN][MAXN];
int N, M;

// number of divisors of n
int F[MAXV + 1];

void solve() {
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  vector<int> fns, fms;
  for (int f = 1; f <= MAXN; ++f) {
    if (N % f == 0) fns.push_back(f);
    if (M % f == 0) fms.push_back(f);
  }

  ll ans = 0;
  for (int fn : fns) for (int fm : fms) {
    if (fn == 1 && fm == 1) continue;
    if (fn == N && fm == M) continue;

    int g = 0;
    for (int i = 0; i < N; i += fn) for (int j = 0; j < M; j += fm) g = gcd(g, A[i][j]);
    assert(g > 0);

    int u = A[0][0] / g, ok = 1;
    for (int i = 0; i < fn; ++i) for (int j = 0; j < fm; ++j) {
      if (A[i][j] % u != 0) ok = 0;
      U[i][j] = A[i][j] / u;
    }
    if (!ok) continue;

    for (int ui = 0; ui < N; ui += fn) for (int uj = 0; uj < M; uj += fm) {
      int m = A[ui][uj] / U[0][0];
      for (int i = 0; i < fn; ++i) for (int j = 0; j < fm; ++j) {
        int val = A[ui + i][uj + j];
        if (val % m != 0) ok = 0;
        if (val / m != U[i][j]) ok = 0;
      }
    }
    if (!ok) continue;

    int ug = 0;
    for (int i = 0; i < fn; ++i) for (int j = 0; j < fm; ++j) ug = gcd(ug, U[i][j]);
    ans += F[ug];
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int i = 1; i <= MAXV; ++i) for (int j = i; j <= MAXV; j += i) ++F[j];

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
