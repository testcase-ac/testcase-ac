#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  int Q; cin >> Q;
  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int l, r, k; cin >> l >> r >> k;

      int cnt = 0;
      for (int i = l; i <= r; ++i) {
        if (A[i] == k) ++cnt;
      }
      cout << cnt << '\n';
    }
    else {
      int l, r; cin >> l >> r;
      for (int i = l; i <= r; ++i) A[i] = -1;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
