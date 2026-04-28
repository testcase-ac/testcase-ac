#include <bits/stdc++.h>
#define pii pair<uint, uint>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

pair<pii, uint> trace(uint m, uint n) {
  pii end_p;
  uint rot;
  if (m == 1) {
    end_p = {1, n};
    rot = 0;
  }
  else if (n == 1) {
    end_p = {m, 1};
    rot = 1;
  }
  else if (m == 2) {
    end_p = {m, 1};
    rot = 2;
  }
  else if (n == 2) {
    end_p = {2, 1};
    rot = 3;
  }
  else {
    uint outer_cycles = (min(m, n) - 1) / 2;
    auto in = trace(m - 2 * outer_cycles, n - 2 * outer_cycles);
    end_p = {in.first.first + outer_cycles, in.first.second + outer_cycles};
    rot = in.second + 4 * outer_cycles;
  }

  return {end_p, rot};
}

int main() {
  fast_io();

  uint m, n;
  cin >> m >> n;

  auto res = trace(m, n);
  cout << res.second << '\n' << res.first.first << ' ' << res.first.second << '\n';
}
