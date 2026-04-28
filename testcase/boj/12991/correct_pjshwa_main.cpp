#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, K;
  cin >> N >> K;

  vector<ll> A(N), B(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> B[i];
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  ll left = 0, right = 1e18; right++;
  while (left < right) {
    ll mid = (left + right) / 2;

    ll cnt = 0;
    for (int i = 0; i < N; i++) {
      ll cleft = 0, cright = N;
      while (cleft < cright) {
        ll cmid = (cleft + cright) / 2;
        if (A[i] * B[cmid] <= mid) cleft = cmid + 1;
        else cright = cmid;
      }

      cnt += cleft;
    }

    if (cnt < K) left = mid + 1;
    else right = mid;
  }

  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
