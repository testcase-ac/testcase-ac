#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000, INF = 0x3f3f3f3f;
int A[MAX + 1][MAX + 1], P[MAX + 1][MAX + 1];

void solve() {
  int N, W, L;
  cin >> N >> W >> L;

  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    A[i][j] = P[i][j] = 0;
  }

  while (W--) {
    int x, y;
    cin >> x >> y;
    A[x][y] = 1;
  }

  for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) {
    P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + A[i][j];
  }

  int left = 1, right = N + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    bool f = false;
    for (int i = mid; i <= N; i++) for (int j = mid; j <= N; j++) {
      int t = P[i][j] - P[i - mid][j] - P[i][j - mid] + P[i - mid][j - mid];
      if (t <= L) {
        f = true;
        break;
      }
    }

    if (f) left = mid + 1;
    else right = mid;
  }

  int l = left - 1;
  cout << l * l << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  cin >> t;
  while (t--) solve();
}
