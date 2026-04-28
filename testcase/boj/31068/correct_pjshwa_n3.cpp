#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
pii A[MAXN + 1];
int Xmax[MAXN + 1], Ymax[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};
  }
  sort(A + 1, A + N + 1);
  for (int i = 1; i <= N; ++i) {
    Xmax[i] = max(Xmax[i - 1], A[i].first);
    Ymax[i] = max(Ymax[i - 1], A[i].second);
  }

  int ans = N + 1;

  // [1, i] [i + 1, j] [j + 1, N]
  for (int i = 1; i <= N - 2; ++i) for (int j = i + 1; j <= N - 1; ++j) {
    bool ok = true;
    for (int k = i + 1; k <= j; ++k) {
      ok &= (A[k].first > Xmax[i] && A[k].second > Ymax[i]);
    }
    for (int k = j + 1; k <= N; ++k) {
      ok &= (A[k].first > Xmax[j] && A[k].second > Ymax[j]);
    }
    if (!ok) continue;

    int a = i, b = j - i, c = N - j;
    ans = min(ans, max({a, b, c}) - min({a, b, c}));
  }

  if (ans == N + 1) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
