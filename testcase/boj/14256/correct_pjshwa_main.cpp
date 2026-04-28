#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  vector<int> squares;
  int i = 0;
  while (1) {
    i++;
    squares.push_back(i * i);
    if (i * i >= 1e5) break;
  }

  int cnt = 0, ni;
  for (int i = 1; i <= n; i++) {
    ni = i;
    for (int sq : squares) {
      if (sq == 1) continue;

      while (ni % sq == 0) ni /= sq;
      if (ni < sq) break;
    }

    for (int sq : squares) {
      if (ni * sq > m) break;
      cnt++;
    }
  }

  cout << cnt << '\n';
}
