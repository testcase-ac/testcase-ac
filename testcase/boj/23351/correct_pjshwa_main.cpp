#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int v[100];

int main() {
  fast_io();

  int n, k, a, b;
  cin >> n >> k >> a >> b;
  assert(2 <= n && n <= 100);
  assert(1 <= k && k <= 100);
  assert(n % a == 0);
  assert(1 <= a * b && a * b < n);
  for (int i = 0; i < n; i++) v[i] = k;

  int ai = 0, day = 1;
  while (1) {
    for (int i = ai; i < ai + a; i++) v[i] += b;
    ai += a;
    if (ai == n) ai = 0;

    for (int i = 0; i < n; i++) {
      if (!--v[i]) return cout << day << '\n', 0;
    }

    day++;
  }
}
