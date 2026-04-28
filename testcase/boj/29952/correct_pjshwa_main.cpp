#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<int, int> precalc = {
  {3, 1},
  {7, 1},
  {15, 5},
  {31, 1},
  {63, 21},
  {127, 1},
  {255, 85},
  {511, 73},
  {1023, 341},
  {2047, 89},
  {4095, 1365},
  {8191, 1},
  {16383, 5461},
  {32767, 4681},
  {65535, 21845},
  {131071, 1},
  {262143, 87381},
  {524287, 1},
  {1048575, 349525},
  {2097151, 299593},
  {4194303, 1398101},
  {8388607, 178481},
  {16777215, 5592405},
  {33554431, 1082401}
};

void solve() {
  int X; cin >> X;
  if (precalc.count(X)) return cout << precalc[X] << '\n', void();

  int ans = 3;
  for (auto& [k, _] : precalc) {
    if (X > k) ans = 2 * ans + 1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  cin >> t;
  while (t--) solve();
}
