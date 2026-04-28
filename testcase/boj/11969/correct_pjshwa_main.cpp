#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5;
int pf[3][MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 3; j++) pf[j][i] += pf[j][i - 1];
    int x;
    cin >> x;
    pf[x - 1][i]++;
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    cout << pf[0][b] - pf[0][a - 1] << ' ';
    cout << pf[1][b] - pf[1][a - 1] << ' ';
    cout << pf[2][b] - pf[2][a - 1] << ' ';
    cout << '\n';
  }
}
