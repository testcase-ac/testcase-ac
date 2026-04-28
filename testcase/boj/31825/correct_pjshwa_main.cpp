#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
int A[MAXN];

void solve() {
  int N, Q; cin >> N >> Q;
  string S; cin >> S;
  for (int i = 0; i < N; ++i) A[i] = S[i] - 'A';

  while (Q--) {
    int op, l, r; cin >> op >> l >> r; --l, --r;
    if (op == 1) {
      int last = -1, cur = 0;
      for (int i = l; i <= r; ++i) {
        if (A[i] != last) {
          last = A[i];
          ++cur;
        }
      }
      cout << cur << '\n';
    }
    else {
      for (int i = l; i <= r; ++i) A[i] = (A[i] + 1) % 26;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
