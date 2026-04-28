#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
bool o[MAX];

int main() {
  fast_io();

  // As a circular board with zero-based index
  int n, z, m;
  cin >> n >> z >> m;
  z--;

  int x;
  for (int i = 0; i < m; i++) cin >> x, o[x - 1] = true;

  for (int k = 1; k <= z; k++) {
    int s = 0;
    for (int g = 0; g < n; g++) {
      s = (s + k) % n;
      if (s == z) return cout << k << '\n', 0;
      if (o[s]) break;
    }
  }
}
