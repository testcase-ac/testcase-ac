#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int a[MAX + 1], t[MAX + 10];

void inc(int v) {
  t[v]--; t[v + 1]++;
}

void dec(int v) {
  t[v]--; t[v - 1]++;
}

void solve() {
  int n, x; cin >> n;
  for (int i = 0; i <= n; i++) {
    cin >> a[i];
    t[a[i]]++;
  }
  cin >> x;

  for (int i = 0; i <= n - x; i++) {
    if (a[i] == 0) continue;

    int zs = a[i], ze = a[i + x];
    dec(zs); inc(ze);

    if (t[1] == 0) {
      cout << "YES\n";
      cout << i << ' ' << i + x << '\n';
      return;
    }

    dec(ze + 1); inc(zs - 1);
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
