#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m; cin >> n >> m;
  vector<int> A(n), B(m);
  for (int i = 0; i < n; i++) cin >> A[i];
  for (int i = 0; i < m; i++) cin >> B[i];
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  int acnt = 1, bcnt = 0;
  while (1) {
    if (acnt && A.size() && B.size()) {
      acnt--;
      bcnt += A.back(); A.pop_back();
    }
    else break;

    while (bcnt && B.size()) {
      bcnt--;
      acnt += B.back(); B.pop_back();
    }
  }
  cout << acnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
