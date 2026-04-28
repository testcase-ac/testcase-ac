#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXK = 12, MAX = 1000;
int d[MAXK][MAX][MAX];

void solve() {
  int N; ll R;
  cin >> N >> R;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> d[0][i][j];

  for (int k = 1; k < MAXK; k++) {
    int z = 1 << k;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
      int v = d[k - 1][i][j];
      if (i + z / 2 < N) v = max(v, d[k - 1][i + z / 2][j]);
      if (j + z / 2 < N) v = max(v, d[k - 1][i][j + z / 2]);
      if (i + z / 2 < N && j + z / 2 < N) v = max(v, d[k - 1][i + z / 2][j + z / 2]);

      d[k][i][j] = v;
    }
  }

  int left = 1, right = N + 1;
  while (left < right) {
    int l = (left + right) / 2;

    // Range maximum query l * l
    auto query = [&](int i, int j) {
      int k = 0;
      while ((1 << k) <= l) k++;
      k--;

      int v = d[k][i][j];
      if (i + l - (1 << k) < N) v = max(v, d[k][i + l - (1 << k)][j]);
      if (j + l - (1 << k) < N) v = max(v, d[k][i][j + l - (1 << k)]);
      if (i + l - (1 << k) < N && j + l - (1 << k) < N) v = max(v, d[k][i + l - (1 << k)][j + l - (1 << k)]);

      return v;
    };

    ll acc = 0;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
      acc += query(i, j);
    }

    if (acc >= R) right = l;
    else left = l + 1;
  }

  if (left == N + 1) cout << "-1\n";
  else cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
