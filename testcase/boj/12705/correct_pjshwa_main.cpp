#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, M, A;
  cin >> N >> M >> A;

  if (A < N * M) {
    int l = A / M, r = A % M;
    cout << "0 " << r << ' ' << l + 1 << ' ' << M << ' ' << l << ' ' << "0\n";
  }
  else if (A == N * M) cout << "0 0 0 " << M << ' ' << N << " 0\n";
  else cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
