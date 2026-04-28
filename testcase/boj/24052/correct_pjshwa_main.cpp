#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX], cnt, n, k;

void assign(int i, int v) {
  a[i] = v;
  if (++cnt == k) {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << '\n';
    exit(0);
  }
}

void insertion_sort() {
  for (int i = 1; i < n; i++) {
    int loc = i - 1, new_item = a[i];
    while (loc >= 0 && new_item < a[loc]) {
      assign(loc + 1, a[loc]);
      loc--;
    }
    if (loc + 1 != i) assign(loc + 1, new_item);
  }
}

void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  insertion_sort();
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
