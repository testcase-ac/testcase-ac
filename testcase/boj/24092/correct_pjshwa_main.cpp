#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX], b[MAX], cnt, n;

void change(int i, int j) {
  if (a[i] == b[i]) cnt--;
  if (a[j] == b[j]) cnt--;
  swap(a[i], a[j]);
  if (a[i] == b[i]) cnt++;
  if (a[j] == b[j]) cnt++;
  if (cnt == n) {
    cout << "1\n";
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
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) cin >> b[i];
  for (int i = 0; i < n; i++) cnt += a[i] == b[i];

  if (cnt == n) return cout << "1\n", void();

  quick_sort(0, n - 1);
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
