#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int a[MAX + 1], b[MAX + 1], inv[MAX + 1];

void solve() {
  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    inv[a[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i];
    b[i] = inv[b[i]];
  }

  bool m_inc = true, m_dec = true;
  for (int i = 2; i <= n; i++) {
    if (b[i] < b[i - 1] && !(b[i] == 1 && b[i - 1] == n)) m_inc = false;
    if (b[i] > b[i - 1] && !(b[i] == n && b[i - 1] == 1)) m_dec = false;
  }

  if (m_inc || m_dec) cout << "good puzzle\n";
  else cout << "bad puzzle\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
