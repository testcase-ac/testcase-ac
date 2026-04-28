#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  int ans = 0, p[N]; iota(p, p + N, 0);
  do {
    int sum = 0;
    for (int i = 0; i < N; ++i) {
      sum += A[p[i]] * A[p[(i + 1) % N]];
    }
    ans = max(ans, sum);
  } while (next_permutation(p, p + N));

  cout << ans << "\n";
  do {
    int sum = 0;
    for (int i = 0; i < N; ++i) {
      sum += A[p[i]] * A[p[(i + 1) % N]];
    }
    if (sum == ans) {
      for (int i = 0; i < N; ++i) cout << A[p[i]] << " ";
      cout << "\n";
      break;
    }

  } while (next_permutation(p, p + N));

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
