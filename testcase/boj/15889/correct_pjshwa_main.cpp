#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30000;
pii X[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> X[i].first;
  for (int i = 1; i <= N - 1; i++) cin >> X[i].second;
  sort(X + 1, X + N + 1);

  int reach = 0;
  for (int i = 1; i <= N; i++) {
    auto [x, w] = X[i];
    if (x > reach) {
      cout << "엄마 나 전역 늦어질 것 같아\n";
      return;
    }
    if (i == N) {
      cout << "권병장님, 중대장님이 찾으십니다\n";
      return;
    }
    reach = max(reach, x + w);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
