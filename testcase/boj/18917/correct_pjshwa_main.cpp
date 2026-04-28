#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int m, op, ox;
  long long s = 0, x = 0;
  cin >> m;

  while (m--) {
    cin >> op;
    if (op == 1) {
      cin >> ox;
      s += ox;
      x ^= ox;
    }
    if (op == 2) {
      cin >> ox;
      s -= ox;
      x ^= ox;
    }
    if (op == 3) cout << s << '\n';
    if (op == 4) cout << x << '\n';
  }
}
