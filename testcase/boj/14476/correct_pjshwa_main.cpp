#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 1e6;
int a[MAX], gl[MAX], gr[MAX];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  gl[0] = a[0];
  gr[n - 1] = a[n - 1];
  for (int i = 1; i < n; i++) {
    gl[i] = __gcd(gl[i - 1], a[i]);
    gr[n - 1 - i] = __gcd(gr[n - i], a[n - 1 - i]);
  }

  int mv = -1, mi, cv;
  for (int i = 0; i < n; i++) {
    if (i == 0) cv = gr[1];
    else if (i == n - 1) cv = gl[n - 2];
    else cv = __gcd(gl[i - 1], gr[i + 1]);

    if (a[i] % cv && cv > mv) {
      mv = cv;
      mi = i;
    }
  }

  if (mv == -1) cout << -1;
  else cout << mv << ' ' << a[mi];
}
