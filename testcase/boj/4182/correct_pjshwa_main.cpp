#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
ll X[MAX], Y[MAX], S[MAX], N, W, vh;

void solve() {
  cin >> W >> vh >> N;
  for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];

  int Z; cin >> Z;
  for (int i = 0; i < Z; ++i) cin >> S[i];
  sort(S, S + Z);

  int left = 0, right = Z;
  while (left < right) {
    int mid = (left + right) / 2;
    int m = S[mid], f = 1;

    ll l = X[0] * m, r = (X[0] + W) * m, y = Y[0];
    for (int i = 1; i < N; ++i) {
      l = max(l - (Y[i] - y) * vh, X[i] * m);
      r = min(r + (Y[i] - y) * vh, (X[i] + W) * m);
      if (r < l) {
        f = 0;
        break;
      }
      y = Y[i];
    }

    if (f) left = mid + 1;
    else right = mid;
  }

  if (left == 0) cout << "IMPOSSIBLE\n";
  else cout << S[left - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
