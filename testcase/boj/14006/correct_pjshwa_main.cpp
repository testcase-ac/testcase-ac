#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 18;
int A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < (1 << N); i++) cin >> A[i];
  if (N == 0) return cout << "YES\n", void();

  sort(A + 1, A + (1 << N));
  for (int i = 1; i < (1 << N); i++) {
    if (A[i] <= A[0]) return cout << "YES\n", void();
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
