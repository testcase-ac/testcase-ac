#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX + 1], d[MAX + 1][2];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  d[1][0] = d[1][1] = A[1];
  for (int i = 2; i <= N; ++i) {
    d[i][0] = d[i - 1][0];
    d[i][1] = d[i - 1][1];

    d[i][0] = max(d[i][0], max(d[i - 2][0], d[i - 2][1]) + A[i]);
    d[i][1] = max(d[i][1], d[i - 1][0] + A[i] / 2);
  }
  cout << max(d[N][0], d[N][1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
