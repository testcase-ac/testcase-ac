#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000, INF = 0x3f3f3f3f;
vector<int> C[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int x, c; cin >> x >> c;
    C[c].push_back(x);
  }

  int ans = 0;
  for (int c = 1; c <= N; c++) {
    sort(C[c].begin(), C[c].end());

    int z = C[c].size();
    for (int i = 0; i < z; i++) {
      int dif = INF;
      for (int j : {i - 1, i + 1}) {
        if (j < 0 || j >= z) continue;
        dif = min(dif, abs(C[c][i] - C[c][j]));
      }
      ans += dif;
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
