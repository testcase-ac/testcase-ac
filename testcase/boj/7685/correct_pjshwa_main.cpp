#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;
void solve() {
  vector<int> A(N); int xor_sum = 0;
  for (int& x : A) cin >> x, xor_sum ^= x;

  int ans = 0;
  for (int x : A) {
    int y = xor_sum ^ x;
    ans += y < x;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
