#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e7;
int a[100'000];
ll qr[MAX + 1];

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  ll score = 0;
  for (int i = 0; i < n; i++) score += a[i];

  int ai = 0;
  for (int i = 1; i <= MAX; i++) {
    score = (score + 2 * ai - n);
    qr[i] = score;

    while (ai < n && a[ai] == i) ai++;
  }

  while (q--) {
    int x;
    cin >> x;
    cout << qr[x] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
