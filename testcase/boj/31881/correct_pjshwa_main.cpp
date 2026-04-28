#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, Q, cnt = 0; cin >> N >> Q;
  vector<int> A(N + 1);
  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int x; cin >> x;
      if (A[x] == 0) ++cnt;
      A[x] = 1;
    }
    if (op == 2) {
      int x; cin >> x;
      if (A[x] == 1) --cnt;
      A[x] = 0;
    }
    if (op == 3) cout << N - cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
