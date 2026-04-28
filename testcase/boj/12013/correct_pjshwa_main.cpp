#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 248;
int A[MAX + 1], d[MAX + 1][MAX + 1];

int r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];
  if (i == j) return d[i][j] = A[i];

  int ret = 0;
  for (int k = i; k < j; k++) {
    int r1 = r(i, k), r2 = r(k + 1, j);
    if (r1 && r1 == r2) ret = max(r1 + 1, ret);
  }

  return d[i][j] = ret;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];

  memset(d, -1, sizeof(d));

  int ans = 0;
  for (int i = 1; i <= N; i++) for (int j = i; j <= N; j++) {
    ans = max(ans, r(i, j));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
