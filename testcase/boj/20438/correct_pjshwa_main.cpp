#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5010;
bool sleep[MAX + 1], present[MAX + 1];
int ppf[MAX + 1];

void solve() {
  int n, k, q, m;
  cin >> n >> k >> q >> m;
  n += 2;
  for (int i = 0, x; i < k; i++) {
    cin >> x;
    sleep[x] = 1;
  }
  for (int i = 0, x; i < q; i++) {
    cin >> x;
    if (sleep[x]) continue;
    for (int j = x; j <= n; j += x) if (!sleep[j]) present[j] = 1;
  }
  for (int i = 1; i <= MAX; i++) {
    ppf[i] = ppf[i - 1];
    if (present[i]) ppf[i]++;
  }
  while (m--) {
    int a, b;
    cin >> a >> b;
    cout << (b - a + 1) - ppf[b] + ppf[a - 1] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
