#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
int A[MAX + 1], d[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  fill(d, d + N + 1, -INF);
  for (int i = 1; i <= N; ++i) {
    for (int j = i - 1; j >= 1; j--) {
      if (d[j] >= A[i]) d[j + 1] = max(d[j + 1], d[j] + A[i]);
    }
    d[1] = max(d[1], A[i]);
  }

  int ans = 0;
  for (int i = 1; i <= N; ++i) {
    if (d[i] > 0) ans = i;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
