#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> A(N); int sum = 0;
  for (int i = 0; i < N; ++i) cin >> A[i], sum += A[i];
  for (int i = 0; i < N; ++i) {
    if (2 * A[i] == sum) return cout << i + 1 << '\n', []{}();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
