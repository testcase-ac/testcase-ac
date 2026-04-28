#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
int C[MAX + 1][MAX + 1], d[MAX + 1];

void solve() {
  int N;
  cin >> N;

  int tot = 0;
  for (int i = 1; i <= N; i++) {
    cin >> d[i], tot += d[i];
    C[i][i] = 1;
  }

  while (tot) {
    // find largest remaining
    int v = -1, x = -1;
    for (int i = 1; i <= N; i++) {
      if (d[i] > v) v = d[i], x = i;
    }

    while (d[x]) {
      int tv = 0, tx = -1;
      for (int i = 1; i <= N; i++) {
        if (C[i][x]) continue;
        if (d[i] > tv) tv = d[i], tx = i;
      }

      d[x]--, d[tx]--;
      C[tx][x] = C[x][tx] = 1;
      cout << tx << ' ' << x << '\n';
      tot -= 2;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
