#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300;
int A[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  int Q; cin >> Q;
  while (Q--) {
    int L, R; cin >> L >> R;

    int it = L;
    for (int i = 1; i <= N; ++i) {
      if (L <= A[i] && A[i] <= R) cout << it++ << ' ';
      else cout << A[i] << ' ';
    }
    cout << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
