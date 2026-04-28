#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5;
int a[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  int x;
  while (m--) {
    cin >> x;
    auto it = lower_bound(a, a + n, x);
    if (it < a + n && *it == x) cout << it - a << '\n';
    else cout << "-1\n";
  }
}
