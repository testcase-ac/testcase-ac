#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
ll W[MAX];
ll fwd[MAX + 1][31], nxt[MAX + 1][31];

void solve() {
  int n, p, k;
  cin >> n >> p >> k;
  for (int i = 0; i < n; i++) cin >> W[i], W[i + n] = W[i];
  for (int i = 1; i < 2 * n; i++) W[i] += W[i - 1];

  ll sum = W[n - 1], cyc = p / sum, rem = p % sum;
  for (int i = 0; i < n; i++) {
    if (rem == 0) {
      fwd[i][0] = cyc * n;
      nxt[i][0] = i;
      continue;
    }

    ll pre = i == 0 ? 0 : W[i - 1];
    int nidx = upper_bound(W, W + 2 * n, pre + p % sum) - W;
    nidx %= n;
    if (nidx < i) nidx += n;

    fwd[i][0] = cyc * n + (nidx - i);
    nxt[i][0] = nidx % n;
  }

  for (int j = 1; j <= 30; j++) for (int i = 0; i < n; i++) {
    nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
    fwd[i][j] = fwd[nxt[i][j - 1]][j - 1] + fwd[i][j - 1];
  }

  ll ans = 0;
  int v = 0;
  for (int b = 30; b >= 0; b--) {
    if (k & (1LL << b)) {
      ans += fwd[v][b];
      v = nxt[v][b];
    }
  }
  cout << ans / n << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
