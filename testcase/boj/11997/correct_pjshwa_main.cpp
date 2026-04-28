#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 1000, MAXP = 5e5;
int xt[MAXP + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  set<int> xs;
  map<int, vector<int>> ys;
  for (int i = 0; i < n; i++) {
    int xi, yi;
    cin >> xi >> yi;
    xi = (xi + 1) / 2;
    yi = (yi + 1) / 2;

    xt[xi]++;
    xs.insert(xi);
    ys[yi].push_back(xi);
  }

  int lw = 0, rw = n, ans = 1e9;
  for (int x : xs) {
    lw += xt[x];
    rw -= xt[x];

    int lu = 0, ru = 0;
    for (auto [yi, xv] : ys) {
      for (int xi : xv) {
        if (xi <= x) lu++;
        else ru++;
      }
      ans = min(ans, max({lu, ru, lw - lu, rw - ru}));
    }
  }

  cout << ans << '\n';
}
