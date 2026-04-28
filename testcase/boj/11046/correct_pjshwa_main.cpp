#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e6;
int str[MAX + 1], plen[MAX + 1];
int n;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

// find longest palindromic span for each element in str
// O(|str|)
void manacher() {
  int r = -1, p = -1;
  for (int i = 0; i < n; ++i) {
    if (i <= r) plen[i] = min((2 * p - i >= 0) ? plen[2 * p - i] : 0, r - i);
    else plen[i] = 0;

    while (
      i - plen[i] - 1 >= 0 && i + plen[i] + 1 < n &&
      str[i - plen[i] - 1] == str[i + plen[i] + 1]
    ) plen[i] += 1;

    if (i + plen[i] > r) {
      r = i + plen[i];
      p = i;
    }
  }
}

int main() {
  fast_io();

  cin >> n;
  n = (n << 1) - 1;

  for (int i = 0; i < n; i++) {
    if (i % 2) str[i] = -1;
    else cin >> str[i];
  }

  manacher();

  int m, a, b;
  cin >> m;
  while (m--) {
    cin >> a >> b;
    a = (a - 1) << 1;
    b = (b - 1) << 1;
    cout << (b - (a + b) / 2 <= plen[(a + b) / 2]) << '\n';
  }
}
