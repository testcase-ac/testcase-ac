#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
int E[MAXN][MAXN], cdist[MAXN][MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    int x; cin >> x;
    E[i][j] = cdist[i][j] = x;
  }

  // Floyd-Warshall
  for (int k = 0; k < N; ++k) for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    cdist[i][j] = min(cdist[i][j], cdist[i][k] + cdist[k][j]);
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i == j) cout << '0';
      else {
        int t = cdist[i][j], ok = 1;
        for (int k = 0; k < N; ++k) {
          if (i == k || j == k) continue;
          if (cdist[i][k] + cdist[k][j] == t) ok = 0;
        }
        cout << ok;
      }
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
