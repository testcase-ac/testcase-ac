#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int A[MAX + 1][MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    cin >> A[i][j];
    A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
  }

  int ans = -INF;
  for (int ei = 1; ei <= N; ei++) for (int ej = 1; ej <= N; ej++) {
    for (int si = 1; si <= ei; si++) for (int sj = 1; sj <= ej; sj++) {
      int sum = A[ei][ej] - A[si - 1][ej] - A[ei][sj - 1] + A[si - 1][sj - 1];
      ans = max(ans, sum);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
