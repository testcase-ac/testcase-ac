#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int a[MAX + 1][MAX + 1];
bool vis1[MAX + 1][MAX + 1], vis2[MAX + 1][MAX + 1];

void solve() {
  int N, M, R;
  cin >> N >> M >> R;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> a[i][j];

  for (int i = 1; i <= min(N, M); i++) {
    int ci = i, cj = i, cdir = 0;
    vector<int> cv;

    while (cdir < 4) {
      if (vis1[ci][cj]) break;

      cv.push_back(a[ci][cj]);
      vis1[ci][cj] = true;
      int ni = ci + dx[cdir], nj = cj + dy[cdir];
      if (ni < 1 || ni > N || nj < 1 || nj > M) {
        cdir++;
        ni = ci + dx[cdir], nj = cj + dy[cdir];
      }
      else if (vis1[ni][nj]) {
        cdir++;
        ni = ci + dx[cdir], nj = cj + dy[cdir];
      }
      ci = ni, cj = nj;
    }

    int z = cv.size();
    ci = i, cj = i, cdir = 0;

    int cvi = 0;
    while (cdir < 4) {
      if (vis2[ci][cj]) break;

      a[ci][cj] = cv[(cvi + R) % z];
      vis2[ci][cj] = true;
      int ni = ci + dx[cdir], nj = cj + dy[cdir];
      if (ni < 1 || ni > N || nj < 1 || nj > M) {
        cdir++;
        ni = ci + dx[cdir], nj = cj + dy[cdir];
      }
      else if (vis2[ni][nj]) {
        cdir++;
        ni = ci + dx[cdir], nj = cj + dy[cdir];
      }
      ci = ni, cj = nj;
      cvi++;
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) cout << a[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
