#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int a, b, p, q, min_diff;
  bool l;
  cin >> a >> b;
  min_diff = abs(a - b);
  if (min_diff) while ((min_diff & 1) == 0) min_diff >>= 1;

  bool able;
  for (int i = 0; i < 5; i++) {
    cin >> p >> q;
    if (a == b) able = p == q;
    else {
      if (a > b) able = p > q && (p - q) % min_diff == 0;
      else able = q > p && (q - p) % min_diff == 0;
    }

    cout << (able ? 'Y' : 'N') << '\n';
  }
}
