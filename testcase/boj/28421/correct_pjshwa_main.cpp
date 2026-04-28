#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX + 1], T[MAX + 1];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    T[A[i]]++;
  }

  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      int x; cin >> x;
      if (x == 0) cout << (N > 1 && T[0] > 0) << '\n';
      else {
        bool ok = false;
        for (int f = 1; f * f <= x; f++) {
          if (x % f) continue;

          if (f == x / f) {
            if (T[f] >= 2) {
              ok = true;
              break;
            }
          }
          else if (T[f] && x / f <= MAX && T[x / f]) {
            ok = true;
            break;
          }
        }
        cout << ok << '\n';
      }
    }
    if (op == 2) {
      int i; cin >> i;
      T[A[i]]--; A[i] = 0; T[0]++;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
