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
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
