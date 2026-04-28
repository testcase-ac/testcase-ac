#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int a[MAX], t[MAX], cnt, n, k;

void change(int i, int v) {
  a[i] = v;
  if (++cnt == k) {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << '\n';
    exit(0);
  }
}

void merge(int p, int q, int r) {
  int i = p, j = q + 1, k = 0;
  while (i <= q && j <= r) {
    if (a[i] <= a[j]) t[k++] = a[i++];
    else t[k++] = a[j++];
  }
  while (i <= q) t[k++] = a[i++];
  while (j <= r) t[k++] = a[j++];

  for (int i = p; i <= r; i++) change(i, t[i - p]);
}

void merge_sort(int p, int r) {
  if (p >= r) return;
  int q = (p + r) / 2;
  merge_sort(p, q);
  merge_sort(q + 1, r);
  merge(p, q, r);
}

void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  merge_sort(0, n - 1);
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
