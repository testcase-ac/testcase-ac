#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e3;
int A[MAX + 1];

void solve() {
  int N, Q;
  cin >> N >> Q;
  for (int i = 1; i <= N; i++) A[i] = i;

  while (Q--) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1) swap(A[x], A[y]);
    if (op == 2) reverse(A + x, A + y + 1);

    bool e = 0;
    for (int i = 1; i <= N; i++) {
      for (int j = i + 1; j <= N; j++) {
        if (A[i] > A[j]) e = !e;
      }
    }
    // for (int i = 1; i <= N; i++) cout << A[i] << ' ';
    // cout << '\n';
    cout << e << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
