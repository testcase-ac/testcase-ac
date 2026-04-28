#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int josephus(int n, int k) {
  if (n == 1) return 0;
  return (josephus(n - 1, k) + k) % n;
}

int main() {
  fast_io();

  while (1) {
    int n, d;
    cin >> n >> d;
    if (n == 0 && d == 0) break;

    int ans = josephus(n, d) + 1;
    cout << n << ' ' << d << ' ' << ans << '\n';
  }
}
