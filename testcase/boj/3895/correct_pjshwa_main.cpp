#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int josephus(int n, int k) {
  if (n == 1) return 0;
  return (josephus(n - 1, k) + k) % n;
}

int main() {
  fast_io();

  int n, k, m;
  while (1) {
    cin >> n >> k >> m;
    if (n == k && k == m && m == 0) break;

    cout << (josephus(n, k) + n + m - k % n) % n + 1 << '\n';
  }
}
