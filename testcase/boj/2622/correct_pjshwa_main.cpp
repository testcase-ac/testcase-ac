#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, cnt = 0;
  cin >> n;
  for (int c = n; c >= 1; c--) {
    for (int b = c; b >= 1; b--) {
      int a = n - (c + b);
      if (a > b) break;
      if (a + b > c) cnt++;
    }
  }

  cout << cnt << '\n';
}
