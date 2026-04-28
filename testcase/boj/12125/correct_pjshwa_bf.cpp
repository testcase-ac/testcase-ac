#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;
void solve_M1() {
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (x > 0) ans += x;
  }
  cout << ans << '\n';
}

void solve_M2() {
  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    A.emplace_back(x, y);
  }
  
  int p[N]; iota(p, p + N, 0);
  int ans = 0;
  do {
    int xacc = 0, yacc = 0;
    for (int i = 0; i < N; ++i) {
      int x = A[p[i]].first, y = A[p[i]].second;
      xacc += x; yacc += y;
      xacc = max(0, xacc); yacc = max(0, yacc);
    }

    assert(xacc >= 0 && yacc >= 0);
    ans = max(ans, xacc + yacc);

  } while (next_permutation(p, p + N));

  cout << ans << '\n';
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int M; cin >> N >> M;
  // cout << "N = " << N << ", M = " << M << '\n';
  if (M == 1) solve_M1();
  else solve_M2();
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
