#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int c2v(char c) {
  if (c == 'A') return 0;
  if (c == 'E') return 1;
  if (c == 'I') return 2;
  if (c == 'O') return 3;
  if (c == 'U') return 4;
}

string A[16];
int z[16];
bool d[1 << 16][5];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    z[i] = A[i].size();
    d[1 << i][c2v(A[i][z[i] - 1])] = true;
  }

  int ans = 0;
  for (int state = 1; state < (1 << N); state++) {
    for (int c = 0; c < N; c++) {
      if (!(state & (1 << c))) continue;

      int v = c2v(A[c][0]);
      d[state][c2v(A[c][z[c] - 1])] |= d[state ^ (1 << c)][v];
    }

    for (int u = 0; u < 5; u++) {
      if (!d[state][u]) continue;

      int cur = 0;
      for (int c = 0; c < N; c++) {
        if (!(state & (1 << c))) continue;
        cur += z[c];
      }
      ans = max(ans, cur);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
