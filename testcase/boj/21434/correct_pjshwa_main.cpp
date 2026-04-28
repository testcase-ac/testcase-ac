#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
pii D1[MAX][MAX], D2[MAX][MAX];
int A[MAX][MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    cin >> A[i][j];
  }
  for (int j1 = 0; j1 < m; j1++) for (int j2 = j1 + 1; j2 < m; j2++) {
    D1[j1][j2] = {-1, -1};
    D2[j1][j2] = {-1, -1};
  }

  for (int i = 0; i < n; i++) {
    for (int j1 = 0; j1 < m; j1++) for (int j2 = j1 + 1; j2 < m; j2++) {
      int val = A[i][j1] + A[i][j2];
      if (D1[j1][j2].second == -1) D1[j1][j2] = {val, i};
      else {
        if (D1[j1][j2].first < val) {
          D2[j1][j2] = D1[j1][j2];
          D1[j1][j2] = {val, i};
        }
        else if (D2[j1][j2].second == -1 || D2[j1][j2].first < val) {
          D2[j1][j2] = {val, i};
        }
      }
    }
  }

  int ans = -0x3f3f3f3f, x1, y1, x2, y2;
  for (int j1 = 0; j1 < m; j1++) for (int j2 = j1 + 1; j2 < m; j2++) {
    auto [t1, t1i] = D1[j1][j2];
    auto [t2, t2i] = D2[j1][j2];

    if (t1 + t2 > ans) {
      ans = t1 + t2;
      if (t1i > t2i) swap(t1i, t2i);
      x1 = t1i + 1, y1 = j1 + 1;
      x2 = t2i + 1, y2 = j2 + 1;
    }
  }

  cout << ans << '\n' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
