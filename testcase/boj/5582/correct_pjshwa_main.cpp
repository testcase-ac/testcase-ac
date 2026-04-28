#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int d[4001][4001];
int main() {
  fast_io();

  string s, t;
  cin >> s >> t;

  int mv = 0;
  for (int i = 1; i <= s.size(); i++) for (int j = 1; j <= t.size(); j++) {
    if (s[i - 1] == t[j - 1]) {
      d[i][j] = d[i - 1][j - 1] + 1;
      mv = max(mv, d[i][j]);
    }
  }
  cout << mv;
}
