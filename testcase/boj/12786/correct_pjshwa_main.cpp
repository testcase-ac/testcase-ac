#include <bits/stdc++.h>
using namespace std;
 
void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e9;
int d[101][21];
bool f[101][21];
int n;

int r(int pos, int hgt) {
  if (pos == n) return 0;

  if (d[pos][hgt] == -1) {
    int mv = MAX;
    if (f[pos + 1][hgt]) mv = min(mv, r(pos + 1, hgt));
    if (hgt + 1 <= 20 && f[pos + 1][hgt + 1]) mv = min(mv, r(pos + 1, hgt + 1));

    int dhgt = min(20, hgt * 2);
    if (f[pos + 1][dhgt]) mv = min(mv, r(pos + 1, dhgt));
    if (hgt > 1 && f[pos + 1][hgt - 1]) mv = min(mv, r(pos + 1, hgt - 1));

    for (int i = 1; i <= 20; i++) {
      if (f[pos + 1][i]) mv = min(mv, 1 + r(pos + 1, i));
    }
    d[pos][hgt] = mv;
  }
  return d[pos][hgt];
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));

  int k, m, mi;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> m;
    for (int j = 0; j < m; j++) {
      cin >> mi;
      f[i + 1][mi] = true;
    }
  }

  int res = r(0, 1);
  cout << (res > k ? -1 : res);
}
