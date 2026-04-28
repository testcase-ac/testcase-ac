#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int lmin[MAX], rmin[MAX];
int main() {
  fast_io();

  int n, s;
  cin >> n >> s;

  for (int i = 0; i < n; i++) cin >> lmin[i], rmin[i] = lmin[i];
  for (int i = 1; i < n; i++) lmin[i] = min(lmin[i], lmin[i - 1]);
  for (int i = n - 2; i >= 0; i--) rmin[i] = min(rmin[i], rmin[i + 1]);

  int mx = lmin[n - 1];
  for (int i = 0; i < n - 1; i++) {
    mx = max(mx, min(lmin[i] + n * s, rmin[i + 1]) - (i + 1) * s);
  }
  cout << mx;
}
