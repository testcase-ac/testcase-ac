#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool bits_odd(int n, int bit) {
  if (bit == 0) return n % 4 == 1 || n % 4 == 2;
  else {
    int intv = 2 << bit;
    int rem = n % intv;
    if (rem < intv / 2) return false;
    else return n % 2 == 0;
  }
}

int main() {
  fast_io();

  int t;
  cin >> t;

  while (t--) {
    int s, f;
    cin >> s >> f;

    int fx = 0, sx = 0;
    for (int bit = 0; bit < 30; bit++) {
      if (bits_odd(f, bit)) fx += (1 << bit);
      if (bits_odd(s - 1, bit)) sx += (1 << bit);
    }

    cout << (fx ^ sx) << '\n';
  }
}
