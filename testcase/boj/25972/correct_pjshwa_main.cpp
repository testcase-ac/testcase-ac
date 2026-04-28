#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int A[MAX + 1][MAX + 1], p[MAX + 1], inv[MAX + 1];

void solve() {
  int N;
  cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; ++i) {
    int x, y;
    cin >> x >> y;
    A[i] = {x, y};
  }
  sort(A.begin(), A.end());

  int ans = 0, f = 0;
  for (int i = 0; i < N; ++i) {
    auto [x, y] = A[i];
    if (!f) ans++;
    f = 0;

    if (i < N - 1) {
      auto [nx, ny] = A[i + 1];
      if (nx <= x + y) f = 1;
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
