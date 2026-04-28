#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int S[MAX + 1];

void solve() {
  int L, N;
  cin >> L >> N;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    S[x] = 1;
  }

  ll ans = 0;
  for (int i = 1; i <= L; i++) {
    if (S[i]) continue;

    int b = log2(i);
    ans += 2 * (i - (1 << b));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
