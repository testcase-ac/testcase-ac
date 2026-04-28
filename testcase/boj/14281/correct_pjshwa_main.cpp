#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 50, INF = 1e18;
int A[MAX], B[MAX];
int N;

void copy() {
  for (int i = 0; i < N; i++) B[i] = A[i];
}

void solve() {
  cin >> N;
  if (N <= 2) return cout << "0\n", void();
  for (int i = 0; i < N; i++) cin >> A[i];

  ll ans = INF;
  for (int i = 1; i < N - 1; i++) {
    copy();

    ll cur = 0;
    for (int j = 1; j <= i; j++) {
      if (B[j - 1] < B[j]) {
        cur += B[j] - B[j - 1];
        B[j] = B[j - 1];
      }
    }
    for (int j = N - 2; j >= i; j--) {
      if (B[j + 1] < B[j]) {
        cur += B[j] - B[j + 1];
        B[j] = B[j + 1];
      }
    }
    ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
