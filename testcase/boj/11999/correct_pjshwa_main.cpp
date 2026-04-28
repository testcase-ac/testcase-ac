#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;

int main() {
  fast_io();

  int x, y, m;
  cin >> x >> y >> m;
  int ms = 0;
  for (int i = 0; i <= MAX; i++) for (int j = 0; j <= MAX; j++) {
    int s = i * x + j * y;
    if (s > m) continue;
    ms = max(ms, s);
  }
  cout << ms << '\n';
}
