#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A[20];
  for (int i = 0; i < 20; ++i) cin >> A[i];

  int sum = 0;
  for (int i = 0; i < 20; ++i) {
    if (A[i] != 20) continue;
    sum += A[i];
    sum += A[(i + 1) % 20];
    sum += A[(i + 19) % 20];
  }
  if (20 * sum > 630) cout << "Alice\n";
  else cout << "Bob\n";
  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
