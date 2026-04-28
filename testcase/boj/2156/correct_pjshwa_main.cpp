#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[10'000], d[10'000];

int rec(int v) {
  if (v == 0) return a[0];
  if (v == 1) return a[0] + a[1];
  if (v == 2) return a[0] + a[1] + a[2] - *min_element(a, a + 3);

  if (d[v] == -1) {
    int res1 = rec(v - 1);
    int res2 = a[v] + rec(v - 2);
    int res3 = a[v] + a[v - 1] + rec(v - 3);
    d[v] = max(res1, max(res2, res3));
  }
  return d[v];
}

int main() {
  fast_io();

  int n;
  cin >> n;

  memset(d, -1, sizeof(d));

  for (int i = 0; i < n; i++) cin >> a[i];
  cout << rec(n - 1) << '\n';
}
