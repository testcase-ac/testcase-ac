#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX], cnt, n, k;

void change(int i, int j) {
  swap(a[i], a[j]);
  if (++cnt == k) {
    for (int u = 0; u < n; u++) cout << a[u] << ' ';
    cout << '\n';
    exit(0);
  }
}

int partition(int p, int r) {
  int x = a[r], i = p - 1;
  for (int j = p; j < r; j++) {
    if (a[j] <= x) change(++i, j);
  }
  if (i + 1 != r) change(i + 1, r);
  return i + 1;
}

void quick_sort(int p, int r) {
  if (p >= r) return;
  int q = partition(p, r);
  quick_sort(p, q - 1);
  quick_sort(q + 1, r);
}

void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  quick_sort(0, n - 1);
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
