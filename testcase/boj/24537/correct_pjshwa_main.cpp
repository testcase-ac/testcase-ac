#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int t[MAX + 1], u[MAX + 1];
bool a[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    t[x]++;
  }

  for (int i = 1; i <= MAX; i++) {
    int g = 0;
    for (int j = i; j <= MAX; j += i) {
      if (t[j]) u[i] += t[j], g = __gcd(g, j);
    }
    a[i] = g == i;
  }

  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;
    if (a[x]) cout << u[x] << '\n';
    else cout << "-1\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
