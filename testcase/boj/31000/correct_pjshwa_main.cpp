#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string C[100];

void solve() {
  int N; cin >> N;

  int ans = (2 * N + 1) * (2 * N + 1);
  for (int a = -N; a <= N; ++a) for (int b = -N; b <= N; ++b) {
    if (a == 0) continue;

    int c = -a - b;
    if (c < -N || c > N) continue;
    ++ans;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
