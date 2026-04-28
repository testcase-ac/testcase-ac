#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 270;
const int dx[4] = {0, 0, 1, 1}, dy[4] = {0, 1, 0, 1};
int B[MAXN][MAXN], N;

inline int get(int i, int j) {
  if (i < 0 || j < 0 || i >= N - 1 || j >= N - 1) return 0;

  const int a = B[i][j];
  const int b = B[i][j + 1];
  const int c = B[i + 1][j];
  const int d = B[i + 1][j + 1];

  int distinct = 1;
  distinct += (b != a);
  distinct += (c != a && c != b);
  distinct += (d != a && d != b && d != c);
  return distinct >= 3;
}

void solve() {
  int K; cin >> N >> K;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> B[i][j];

  int sum = 0;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) sum += get(i, j);

  int ans = sum;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int cur = sum;
    for (int k = 0; k < 4; ++k) {
      int x = i - dx[k], y = j - dy[k];
      cur -= get(x, y);
    }

    int pre = B[i][j];
    for (int l = 1; l <= min(10, K); ++l) {
      B[i][j] = l; int acc = 0;
      for (int k = 0; k < 4; ++k) {
        int x = i - dx[k], y = j - dy[k];
        acc += get(x, y);
      }
      ans = max(ans, cur + acc);
    }
    if (K > 10) {
      B[i][j] = -1; int acc = 0;
      for (int k = 0; k < 4; ++k) {
        int x = i - dx[k], y = j - dy[k];
        acc += get(x, y);
      }
      ans = max(ans, cur + acc);
    }
    B[i][j] = pre;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
