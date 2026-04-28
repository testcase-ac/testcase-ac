#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int A[MAX + 1][MAX + 1], B[MAX + 1][MAX + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int R, C;
  cin >> R >> C;

  int v1 = 0, v2 = 0;
  for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) v1 += A[i][j];
  for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) v2 += B[i][j];
  cout << max(v1, v2) << '\n';
}

int main() {
  fast_io();

  for (int i = 1; i <= MAX; i++) for (int j = 1; j <= MAX; j++) {
    A[i][j] = !((i % 3 == 0) ^ (j % 3 == 0));
    B[i][j] = (i + j) % 3 != 1;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
