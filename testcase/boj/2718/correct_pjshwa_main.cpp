#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int d[22];
int main() {
  fast_io();

  d[0] = 1;
  d[1] = 1;
  d[2] = 5;
  d[3] = 11;
  for (int i = 4; i < 22; i++) d[i] = d[i - 1] + 5 * d[i - 2] + d[i - 3] - d[i - 4];

  int t, n;
  cin >> t;

  while (t--) {
    cin >> n;
    cout << d[n] << '\n';
  }
}
