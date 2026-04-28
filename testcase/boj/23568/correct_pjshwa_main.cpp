#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

unordered_map<int, int> ops;

int main() {
  fast_io();

  int m;
  cin >> m;
  while (m--) {
    int i, k;
    string j;
    cin >> i >> j >> k;
    if (j == "L") k = -k;
    ops[i] = k;
  }

  int c;
  cin >> c;
  while (ops.count(c)) c += ops[c];
  cout << c << '\n';
}
