#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
int d[7][MAX + 1];

void solve() {
  string S;
  cin >> S;

  for (int i = 0; i < 7; i++) fill(d[i], d[i] + MAX + 1, INF);
  
  d[0][0] = 0;
  for (int i = 1; i <= S.size(); i++) {
    char c = S[i - 1];
    d[1][i] = min(d[1][i], d[0][i - 1] + (c != 'B'));
    d[1][i] = min(d[1][i], d[1][i - 1] + (c != 'B'));
    d[2][i] = min(d[2][i], d[1][i - 1] + (c != 'A'));
    d[3][i] = min(d[3][i], d[2][i - 1] + (c != 'N'));
    d[4][i] = min(d[4][i], d[3][i - 1] + (c != 'A'));
    d[5][i] = min(d[5][i], d[4][i - 1] + (c != 'N'));
    d[6][i] = min(d[6][i], d[5][i - 1] + (c != 'A'));
    d[5][i] = min(d[5][i], d[6][i - 1] + (c != 'N'));
    d[1][i] = min(d[1][i], d[6][i - 1] + (c != 'B'));
  }

  cout << d[6][S.size()] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
