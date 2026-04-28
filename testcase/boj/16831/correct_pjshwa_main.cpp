#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN];

void solve() {
  int N, sum = 0; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i], sum ^= A[i];

  bool o = false;
  if (sum == 0) {
    for (int i = 0; i < N; ++i) {
      if (A[i] & 1) o = true;
    }
  } else {
    o = sum != 1;
  }
  cout << (o ? "Alice" : "Bob") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
