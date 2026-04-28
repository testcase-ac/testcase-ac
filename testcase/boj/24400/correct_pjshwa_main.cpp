#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int a[MAX], b[MAX], n, ccnt;
bitset<MAX> ident;

void swap_track(int i, int j) {
  if (a[i] == b[i] && a[j] != b[i]) {
    if (ident[i]) ccnt--;
    ident[i] = 0;
  }
  if (a[j] == b[j] && a[i] != b[j]) {
    if (ident[j]) ccnt--;
    ident[j] = 0;
  }
  if (a[i] != b[i] && a[j] == b[i]) {
    if (!ident[i]) ccnt++;
    ident[i] = 1;
  }
  if (a[j] != b[j] && a[i] == b[j]) {
    if (!ident[j]) ccnt++;
    ident[j] = 1;
  }

  swap(a[i], a[j]);
  if (ccnt == n) {
    cout << "1\n";
    exit(0);
  }
}

void solve() {
  int q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    ident[i] = a[i] == b[i];
    if (ident[i]) ccnt++;
  }

  if (ccnt == n) return cout << "1\n", void();

  int left = 0, right = n - 1;
  while (1) {
    if (left == right) break;

    int x = a[right], i = left - 1;
    for (int j = left; j < right; j++) {
      if (a[j] <= x) swap_track(++i, j);
    }
    if (i + 1 != right) swap_track(i + 1, right);

    int t = i + 1, k = t - left + 1;
    if (q < k) right = t - 1;
    else if (q == k) break;
    else {
      q -= k;
      left = t + 1;
    }
  }

  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
