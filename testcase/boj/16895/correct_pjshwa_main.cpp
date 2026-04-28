#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e3;
int A[MAX];

void solve() {
  int N;
  cin >> N;

  int x = 0;
  for (int i = 0; i < N; i++) cin >> A[i], x ^= A[i];

  int ans = 0;
  for (int i = 0; i < N; i++) {
    x ^= A[i];
    if (x < A[i]) ans++;
    x ^= A[i];
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
