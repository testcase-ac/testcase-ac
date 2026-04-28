#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_odd(int n) {
  return n & 1;
}

void solve() {
  int N, M; cin >> N >> M;
  if (is_odd(N) != is_odd(M)) cout << 'A';
  else {
    if (N > M) swap(N, M);
    int pw = 1;
    while (N % 2 == 0) N /= 2, pw *= 2;
    if (M % pw == 0 && is_odd(M / pw)) cout << 'B';
    else cout << 'A';
  }
  cout << " player wins\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
