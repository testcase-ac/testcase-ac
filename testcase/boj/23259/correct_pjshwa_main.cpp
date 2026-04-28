#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int pair_to_bit(int a, int b) {
  if (a > b) swap(a, b);

  int res;
  if (a == 0) res = b - 1;
  if (a == 1) res = 2 + b;
  if (a == 2) res = 4 + b;
  if (a == 3) res = 5 + b;
  return 1 << res;
}

int group[1 << 10];

int main() {
  fast_io();

  int gnum = 0;
  for (int mask = 0; mask < (1 << 10); mask++) {
    if (group[mask]) continue;
    gnum++;

    int a[5] = {0, 1, 2, 3, 4};

    do {
      int cmask = 0;
      for (int i = 0; i < 5; i++) for (int j = i + 1; j < 5; j++) {
        if (mask & pair_to_bit(i, j)) cmask |= pair_to_bit(a[i], a[j]);
      }
      group[cmask] = gnum;
    } while (next_permutation(a, a + 5));
  }

  int n;
  cin >> n;

  map<int, int> gcount;
  for (int i = 1; i <= n; i++) {
    int e, cmask = 0;
    cin >> e;
    while (e--) {
      int x, y;
      cin >> x >> y;
      cmask |= pair_to_bit(x - 1, y - 1);
    }

    gcount[group[cmask]]++;
  }

  int ans = 0;
  for (auto [k, v] : gcount) {
    if (v == 1) ans++;
  }
  cout << ans << '\n';
}
