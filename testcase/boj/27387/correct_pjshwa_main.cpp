#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int A[MAXN + 1];

void solve() {
  int N, M; cin >> N >> M;
  iota(A + 1, A + N + 1, 1);
  while (M--) {
    int x; cin >> x;
    swap(A[x], A[x + 1]);
  }
  for (int i = 1; i <= N; ++i) cout << A[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
