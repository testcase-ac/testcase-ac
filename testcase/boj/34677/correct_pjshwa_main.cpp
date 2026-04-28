#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3000;
int A[MAXN], B[MAXN], E[MAXN][MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> B[i];

  for (int i = 0; i < N; ++i) {
    int amini = i, aminv = A[i], bmini = i, bminv = B[i];
    E[i][i] = 1;
    for (int j = i + 1; j < N; ++j) {
      if (A[j] < aminv) aminv = A[j], amini = j;
      if (B[j] < bminv) bminv = B[j], bmini = j;
      E[i][j] = amini == bmini;
    }
  }

  int ans = 0, i = 0;
  while (i < N) {
    int j = N - 1;
    while (!E[i][j]) --j;
    ++ans; i = j + 1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
