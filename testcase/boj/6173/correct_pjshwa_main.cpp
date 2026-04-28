#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int C[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;
  int H, acc = 0, lhalf = 0;
  for (int i = 1; i <= K; ++i) {
    cin >> C[i];
    acc += C[i];
    if (acc <= N / 2) H = i, lhalf = acc;
  }

  int i = H + 1, j = K, rhalf = N - lhalf;
  while (rhalf > lhalf) {
    while (C[i] == 0) ++i;
    while (C[j] == 0) --j;

    assert(i != j);
    cout << i << ' ' << j << '\n';

    --C[i]; --C[j]; rhalf -= 2;
  }

  i = 1, j = K;
  while (1) {
    while (i <= K && C[i] == 0) ++i;
    while (j >= 1 && C[j] == 0) --j;
    if (i > j) break;

    assert(i != j);
    cout << i << ' ' << j << '\n';

    --C[i]; --C[j];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
