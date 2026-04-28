#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4, INF = 0x3f3f3f3f;
int d[MAX + 1];
pii A[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i].first >> A[i].second;
  sort(A + 1, A + N + 1);

  fill(d, d + N + 1, INF);
  d[0] = 0;
  for (int i = 1; i <= N; i++) {
    auto [ox, oy] = A[i];
    int miny = min(0, oy), maxy = max(0, oy), minx = ox;

    for (int j = i - 1; j >= 0; j--) {
      int cost = max(ox - minx, 2 * max(maxy, -miny));
      d[i] = min(d[i], d[j] + cost);

      auto [px, py] = A[j];
      miny = min(miny, py);
      maxy = max(maxy, py);
      minx = min(minx, px);
    }
  }

  cout << d[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
