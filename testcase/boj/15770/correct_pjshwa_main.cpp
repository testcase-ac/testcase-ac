#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
bool p[MAX + 1][MAX + 1];
int d[MAX + 1][MAX + 1];
char cur[MAX + 1];

void solve() {
  int n;
  cin >> n;

  cin.ignore();
  int sz = 0;
  for (int i = 0; i < n; i++) {
    cin >> cur[sz++];
    if (cur[sz - 1] == '-') sz -= 2;

    int e = sz - 1;
    d[e][e] = p[e][e] = 1;
    for (int j = e - 1; j >= 0; j--) {
      if (j == e - 1) p[e][j] = cur[j] == cur[e];
      else p[e][j] = p[e - 1][j + 1] && cur[j] == cur[e];
    }
    for (int j = e - 1; j >= 0; j--) {
      d[e][j] = d[e][j + 1] + d[e - 1][j] - d[e - 1][j + 1] + p[e][j];
    }
    cout << d[e][0] << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
