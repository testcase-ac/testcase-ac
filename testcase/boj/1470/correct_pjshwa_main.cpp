#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, L; cin >> N >> L;
  int A[3]; cin >> A[0] >> A[1] >> A[2];
  A[0] += L;

  int base = 0; vector<pii> C;
  for (int i = 1; i < N; ++i) {
    int a[3]; cin >> a[0] >> a[1] >> a[2];
    if (a[0] > A[0]) ++base;
    else if (a[0] == A[0]) {
      int needa = max(0, A[1] - a[1]);
      int needb = max(0, A[2] - a[2]);
      if (needa <= L && needb <= L && needa + needb <= L) {
        C.emplace_back(needa, needb);
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
