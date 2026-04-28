#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<ll> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A.begin(), A.end());

  vector<ll> C;
  while (!A.empty()) {
    ll x = A.back(); A.pop_back();
    if (A.empty()) break;

    ll y = A.back();
    if (x == y) C.push_back(x), A.pop_back();
    else if (x == y + 1) C.push_back(y), A.pop_back();
  }

  sort(C.begin(), C.end());
  ll ans = 0;
  while (C.size() >= 2) {
    ll x = C.back(); C.pop_back();
    ll y = C.back(); C.pop_back();
    ans += x * y;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
