#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  for (int i = 1; i < N; ++i) {
    int l = i;
    for (int j = i - 1; j >= 0; --j) {
      if (__gcd(A[j], A[i]) != 1) break;
      if (A[j] > A[i]) l = j;
    }
    for (int j = i; j > l; --j) swap(A[j], A[j - 1]);
  }

  for (int i = 0; i < N; ++i) cout << A[i] << " ";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
