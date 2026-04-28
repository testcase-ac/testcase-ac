#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e9 + 7;
int n, d[1000];
string s;

int r(int i) {
  if (i == n - 1) return 0;

  if (d[i] == -1) {
    char nchar = s[i] == 'B' ? 'O' : s[i] == 'O' ? 'J' : 'B';
    int mv = MAX;
    for (int j = i + 1; j < n; j++) {
      int q = j - i;
      if (s[j] == nchar) mv = min(mv, q * q + r(j));
    }
    d[i] = mv;
  }
  return d[i];
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));
  cin >> n >> s;
  int res = r(0);
  cout << (res == MAX ? -1 : res);
}
