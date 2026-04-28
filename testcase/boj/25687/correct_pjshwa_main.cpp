#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
int a[MAX][MAX];

void solve() {
  int N;
  cin >> N;

  int it = N * N, d = 0, i = 0;
  while (it--) {
    int x = i, y = i + d;
    a[x][y] = it + 1;

    if (d >= 0) i++;
    else i--;

    if (i < 0 || i >= N || i + d < 0 || i + d >= N) {
      if (d <= 0) d = -d + 1;
      else d = -d;

      if (d < 0) i = N - 1;
      else i = 0;
    }
  }

  // for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
  //   if (a[i][j] == 0) a[i][j] = it--;
  // }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) cout << a[i][j] << ' ';
    cout << '\n';
  }

  a[0][0] = 1, a[0][1] = 2, a[0][2] = 3, a[0][3] = 4;
  a[1][0] = 5, a[1][1] = 7, a[1][2] = 9, a[1][3] = 11;
  a[2][0] = 13, a[2][1] = 15, a[2][2] = 6, a[2][3] = 8;
  a[3][0] = 10, a[3][1] = 12, a[3][2] = 14, a[3][3] = 16;

  double xscore = 9999999999;
  for (int i = 0; i < N; i++) {
    for (int j1 = 0; j1 < N; j1++) for (int j2 = j1 + 1; j2 < N; j2++) {
      if (a[i][j1] > a[i][j2]) xscore = min(xscore, (double)a[i][j1] / a[i][j2]);
      else xscore = min(xscore, (double)a[i][j2] / a[i][j1]);
    }
  }
  for (int j = 0; j < N; j++) {
    for (int i1 = 0; i1 < N; i1++) for (int i2 = i1 + 1; i2 < N; i2++) {
      if (a[i1][j] > a[i2][j]) xscore = min(xscore, (double)a[i1][j] / a[i2][j]);
      else xscore = min(xscore, (double)a[i2][j] / a[i1][j]);
    }
  }

  cout << fixed << setprecision(10) << xscore << endl;

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
