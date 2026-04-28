#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5, INF = 0x3f3f3f3f;
int A[MAX + 1]; pii dl[MAX + 10], dr[MAX + 10];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> A[i];

  dl[1] = {1, INF}; dr[n] = {1, INF};
  dl[0] = dr[n + 1] = {0, INF};
  for (int i = 2; i <= n; ++i) {
    auto [ps, pd] = dl[i - 1];
    int d = A[i] - A[i - 1];

    if (pd == d) {
      dl[i] = {ps + 1, d};
    }
    else {
      dl[i] = {2, d};
    }
  }
  for (int i = n - 1; i >= 1; --i) {
    auto [ps, pd] = dr[i + 1];
    int d = A[i + 1] - A[i];

    if (pd == d) {
      dr[i] = {ps + 1, d};
    }
    else {
      dr[i] = {2, d};
    }
  }

  int ans = 2;
  for (int i = 1; i <= n; i++) {
    auto [ls, ld] = dl[i - 1];
    auto [rs, rd] = dr[i + 1];
    ans = max({ans, ls + 1, rs + 1});

    if (ld != INF && i > 1 && i < n) {
      if (A[i - 1] + ld == A[i + 1] - ld) {
        ans = max(ans, ls + 2);
        if (ld == rd) ans = max(ans, ls + rs + 1);
      }
    }
    if (rd != INF && i > 1 && i < n) {
      if (A[i - 1] + rd == A[i + 1] - rd) {
        ans = max(ans, rs + 2);
        if (ld == rd) ans = max(ans, ls + rs + 1);
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
