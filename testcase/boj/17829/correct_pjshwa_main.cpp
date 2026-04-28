#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1024;
int a[MAX][MAX];

int r(int si, int sj, int ei, int ej) {
  if (si + 1 == ei) return a[si][sj];

  int midi = (si + ei) / 2, midj = (sj + ej) / 2;
  vector<int> u{r(si, sj, midi, midj), r(midi, sj, ei, midj), r(si, midj, midi, ej), r(midi, midj, ei, ej)};
  sort(u.begin(), u.end());
  return u[2];
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
  cout << r(0, 0, n, n) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
