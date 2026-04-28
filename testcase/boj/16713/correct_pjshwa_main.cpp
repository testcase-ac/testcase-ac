#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX + 1];

void solve() {
  int N, Q;
  cin >> N >> Q;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 2; i <= N; i++) A[i] ^= A[i - 1];

  int ans = 0;
  while (Q--) {
    int l, r;
    cin >> l >> r;
    ans ^= (A[r] ^ A[l - 1]);
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
