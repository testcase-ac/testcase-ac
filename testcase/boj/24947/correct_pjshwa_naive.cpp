#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, INF = 0x3f3f3f3f;
int X[MAX], Y[MAX], Z[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> X[i] >> Y[i] >> Z[i];

  int ans = -1;
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) for (int k = j + 1; k < N; k++) {
    bool adv_i = (X[i] > X[j] && X[i] > X[k]) || (Y[i] > Y[j] && Y[i] > Y[k]) || (Z[i] > Z[j] && Z[i] > Z[k]);
    bool adv_j = (X[j] > X[i] && X[j] > X[k]) || (Y[j] > Y[i] && Y[j] > Y[k]) || (Z[j] > Z[i] && Z[j] > Z[k]);
    bool adv_k = (X[k] > X[i] && X[k] > X[j]) || (Y[k] > Y[i] && Y[k] > Y[j]) || (Z[k] > Z[i] && Z[k] > Z[j]);

    if (adv_i && adv_j && adv_k) {
      ans = max(ans, max({X[i], X[j], X[k]}) + max({Y[i], Y[j], Y[k]}) + max({Z[i], Z[j], Z[k]}));
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
