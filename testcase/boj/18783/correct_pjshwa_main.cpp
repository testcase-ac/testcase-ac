#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

void swap(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int f[100'001][31];
int main() {
  fast_io();

  int n, m, k, li, ri;
  cin >> n >> m >> k;

  for (int i = 1; i <= n; i++) f[i][0] = i;

  while (m--) {
    cin >> li >> ri;
    for (int i = 0; i <= (ri - li) / 2; i++) {
      if (li + i != ri - i) swap(f[li + i][0], f[ri - i][0]);
    }
  }

  for (int j = 0; j < 30; j++)
    for (int i = 1; i <= n; i++) f[i][j + 1] = f[f[i][j]][j];

  int ok = k, ny;
  for (int y = 1; y <= n; y++) {
    k = ok;
    ny = y;
    for (int i = 0; k; i++) {
      if (k & 1) ny = f[ny][i];
      k >>= 1;
    }
    cout << ny << '\n';
  }
}
