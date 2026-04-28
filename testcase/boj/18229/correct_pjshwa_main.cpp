#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int A[MAX + 1][MAX + 1], U[MAX + 1];

void solve() {
  int N, M, K;
  cin >> N >> M >> K;
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> A[i][j];
  
  for (int j = 1; j <= M; j++) {
    for (int i = 1; i <= N; i++) {
      U[i] += A[i][j];
      if (U[i] >= K) {
        cout << i << ' ' << j << '\n';
        return;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
