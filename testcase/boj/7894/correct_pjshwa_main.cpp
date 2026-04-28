#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int tt, n;
  double s;
  cin >> tt;

  while (tt--) {
    cin >> n;

    // Stirling's formula
    s = (n + 0.5) * log(n) - n + 0.9189;
    s /= log(10);
    cout << (int)s + 1 << '\n';
  }
}
