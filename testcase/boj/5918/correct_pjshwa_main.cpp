#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000, INF = 1e9 + 7;
int a[MAX], d[MAX], c[100000];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) cin >> c[i];
  for (int i = m - 2; i >= 0; i--) {
    if (c[i] >= c[i + 1]) c[i] = c[i + 1];
  }
  sort(a, a + n);
  fill(d, d + n, INF);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      int dist = a[i] - a[j] + 1;
      d[i] = min(d[i], c[dist - 1] + (j > 0 ? d[j - 1] : 0));
    }
  }

  cout << d[n - 1] << '\n';
}
