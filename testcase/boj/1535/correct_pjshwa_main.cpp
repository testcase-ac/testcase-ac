#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20;
int L[MAX], H[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> L[i];
  for (int i = 0; i < N; i++) cin >> H[i];

  int ans = 0;
  for (int s = 0; s < (1 << N); s++) {
    int pow = 0, joy = 0;
    for (int i = 0; i < N; i++) {
      if (s & (1 << i)) {
        pow += L[i];
        joy += H[i];
      }
    }
    if (pow < 100) ans = max(ans, joy);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
