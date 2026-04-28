#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int INF = 1e9 + 7;
int a[1000][1000], d2[1000][1000], d5[1000][1000];
int main() {
  fast_io();

  int n, s, sc;
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
      if (a[i][j] == 0) d2[i][j] = d5[i][j] = INF;
    }
  }

  s = a[0][0];
  while (s % 2 == 0) {
    s /= 2;
    d2[0][0]++;
  }
  while (s % 5 == 0) {
    s /= 5;
    d5[0][0]++;
  }

  for (int i = 1; i < n; i++) {
    s = a[i][0];
    if (s == 0) continue;

    sc = 0;
    while (s % 2 == 0) {
      s /= 2;
      sc++;
    }
    d2[i][0] = d2[i - 1][0] + sc;

    sc = 0;
    while (s % 5 == 0) {
      s /= 5;
      sc++;
    }
    d5[i][0] = d5[i - 1][0] + sc;
  }

  for (int i = 1; i < n; i++) {
    s = a[0][i];
    if (s == 0) continue;

    sc = 0;
    while (s % 2 == 0) {
      s /= 2;
      sc++;
    }
    d2[0][i] = d2[0][i - 1] + sc;

    sc = 0;
    while (s % 5 == 0) {
      s /= 5;
      sc++;
    }
    d5[0][i] = d5[0][i - 1] + sc;
  }


  for (int i = 1; i < n; i++) {
    for (int j = 1; j < n; j++) {
      s = a[i][j];
      if (s == 0) continue;

      sc = 0;
      while (s % 2 == 0) {
        s /= 2;
        sc++;
      }
      d2[i][j] = min(d2[i - 1][j], d2[i][j - 1]) + sc;

      sc = 0;
      while (s % 5 == 0) {
        s /= 5;
        sc++;
      }
      d5[i][j] = min(d5[i - 1][j], d5[i][j - 1]) + sc;
    }
  }

  cout << min(d2[n - 1][n - 1], d5[n - 1][n - 1]) << '\n';
}
