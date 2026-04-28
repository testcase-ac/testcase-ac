#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int x[51];
void f(int s, int e, int c) {
  if (s > e) return;

  int m = (s + e) / 2;
  x[m] = c;

  f(s, m - 1, c + 1);
  f(m + 1, e, c + 1);
}

int main() {
  fast_io();

  f(1, 50, 1);
  while (1) {
    int n;
    cin >> n;
    if (n == 0) break;

    int y = x[(n + 1) / 2];
    if (n & 1) y++;
    cout << y << '\n';
  }
}
