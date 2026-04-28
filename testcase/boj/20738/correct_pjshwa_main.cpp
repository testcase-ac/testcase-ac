#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ld = long double;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int pts[MAX];
int n;

ld f(ld a) {
  ld ret = 0;
  for (int i = 0; i < n; i++) ret += (a - pts[i]) * (a - pts[i]);
  return ret;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    pts[i] = y - x;
  }

  ld left = -3e6, right = 3e6;

  // Ternary search
  for (int i = 0; i < 100; i++) {
    ld mid1 = left + (right - left) / 3;
    ld mid2 = right - (right - left) / 3;
    if (f(mid1) < f(mid2)) right = mid2;
    else left = mid1;
  }
  cout << fixed << setprecision(6) << left << '\n';
}
