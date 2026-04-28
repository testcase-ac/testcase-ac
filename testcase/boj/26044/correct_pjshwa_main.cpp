#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int LIM = 1e9;
map<int, int> R;

void solve() {
  int N;
  cin >> N;
  if (N == 1) return cout << "1\n", void();

  int ans = N + 1;
  if (R.count(N)) ans = min(ans, R[N]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  for (int k = 2; k <= 18; k++) {
    for (int n = k;; n++) {
      __int128_t C = 1;
      for (int i = 0; i < k; i++) {
        C *= n - i;
        C /= i + 1;
      }
      if (C > LIM) break;

      if (R.count(C)) R[C] = min(R[C], n + 1);
      else R[C] = n + 1;
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
