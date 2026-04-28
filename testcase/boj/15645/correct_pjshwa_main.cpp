#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
const int dy[3] = {-1, 0, 1};
int A[MAX][3], d1[MAX][3], d2[MAX][3];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) for (int j = 0; j < 3; j++) cin >> A[i][j];

  for (int j = 0; j < 3; j++) d1[0][j] = d2[0][j] = A[0][j];
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < 3; j++) {
      d2[i][j] = INF;

      for (int k = 0; k < 3; k++) {
        int pi = i - 1, pj = dy[j] + k;
        if (pj < 0 || pj >= 3) continue;

        d1[i][j] = max(d1[i][j], d1[pi][pj] + A[i][j]);
        d2[i][j] = min(d2[i][j], d2[pi][pj] + A[i][j]);
      }
    }
  }

  cout << *max_element(d1[N - 1], d1[N - 1] + 3) << ' ';
  cout << *min_element(d2[N - 1], d2[N - 1] + 3) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
