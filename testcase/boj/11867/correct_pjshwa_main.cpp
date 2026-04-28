#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  if ((n & 1) && (m & 1)) cout << 'B';
  else cout << 'A';
}
