#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX], C[10], sz;

void inc(int type) {
  if (C[type]++ == 0) ++sz;
}

void dec(int type) {
  if (--C[type] == 0) --sz;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  int r = 0, ans = 0;
  for (int l = 0; l < N; ++l) {
    while (r < N) {
      if (sz == 2 && C[A[r]] == 0) break;
      inc(A[r++]);
    }
    ans = max(ans, r - l);
    dec(A[l]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
