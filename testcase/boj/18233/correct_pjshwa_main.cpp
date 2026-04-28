#include <bits/stdc++.h>
#define pll pair<ll, ll>
#define pllpi pair<pll, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 20;
int lb[MAX], ub[MAX], g[MAX];

int main() {
  fast_io();

  int n, p, e;
  cin >> n >> p >> e;
  for (int i = 0; i < n; i++) cin >> lb[i] >> ub[i];

  for (int state = 0; state < (1 << n); state++) {
    if (__builtin_popcount(state) != p) continue;
    int l = 0, u = 0;
    for (int i = 0; i < n; i++) {
      if (state & (1 << i)) {
        l += lb[i];
        u += ub[i];
      }
    }

    if (l <= e && e <= u) {
      for (int i = 0; i < n; i++) {
        if (state & (1 << i)) g[i] = lb[i], e -= lb[i];
      }
      for (int i = 0; i < n; i++) {
        if (state & (1 << i)) {
          int diff = min(ub[i], g[i] + e) - g[i];
          e -= diff;
          g[i] += diff;
        }
      }
      for (int i = 0; i < n; i++) cout << g[i] << " ";
      cout << '\n';
      return 0;
    }
  }

  cout << "-1\n";
}
