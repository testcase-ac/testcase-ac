#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int A[MAXN], Bl[MAXN + 1], Bu[MAXN + 1];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  for (int m = 2; m <= MAXN; ++m) {
    Bl[m] = min(A[0] % m, A[N - 1] % m);
    Bu[m] = max(A[0] % m, A[N - 1] % m);
    for (int w = 0; w <= MAXN; w += m) {
      int it = lower_bound(A, A + N, w) - A;
      for (int i = it - 1; i <= it; ++i) {
        if (i < 0 || i >= N) continue;
        int b = A[i] % m;
        Bl[m] = min(Bl[m], b);
        Bu[m] = max(Bu[m], b);
      }
    }
  }

  while (Q--) {
    int m; cin >> m;
    cout << Bl[m] << ' ' << Bu[m] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
