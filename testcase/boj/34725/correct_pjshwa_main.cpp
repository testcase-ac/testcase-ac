#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN][MAXN];

void solve() {
  int N, M; cin >> N >> M;

  int c = 0;
  for (int i = 0; i < N / 2; ++i) for (int j = 0; j < M / 2; ++j) A[i][j] = ++c;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cout << A[i % (N / 2)][j % (M / 2)] << " ";
    }
    cout << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
