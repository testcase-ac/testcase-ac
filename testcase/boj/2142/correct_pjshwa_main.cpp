#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
int A[MAXN];
vector<int> D[2];

void solve() {
  int N, M, Z, ok = 1; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    int r = i % 2; D[r].clear();
    for (int j = 0; j < M; ++j) cin >> A[j];
    for (int j = 0; j < M; ++j) for (int k = j + 1; k < M; ++k) {
      D[r].push_back(A[j] - A[k]);
    }

    if (i == 0) Z = D[r].size();
    else {
      for (int j = 0; j < Z; ++j) {
        if (D[r][j] < D[r ^ 1][j]) ok = 0;
      }
    }
  }

  if (ok) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
