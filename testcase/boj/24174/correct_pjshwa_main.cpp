#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int a[MAX], cnt, n, k;

void change(int i, int j) {
  swap(a[i], a[j]);
  if (++cnt == k) {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << '\n';
    exit(0);
  }
}

void heapify(int u, int n) {
  int l = u * 2 + 1, r = u * 2 + 2, m = u;
  if (r < n) {
    if (a[r] < a[l]) m = r;
    else m = l;
  }
  else if (l < n) m = l;
  else return;

  if (a[m] < a[u]) {
    change(u, m);
    heapify(m, n);
  }
}

void build_min_heap() {
  for (int i = n / 2 - 1; i >= 0; i--) heapify(i, n);
}

void heap_sort() {
  build_min_heap();
  for (int i = n - 1; i > 0; i--) {
    change(0, i);
    heapify(0, i);
  }
}

void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  heap_sort();
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
