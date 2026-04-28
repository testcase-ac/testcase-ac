#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[200001];
int main() {
  fast_io();

  int n, q, ai;
  cin >> n >> q;

  for (int i = 2; i <= n; i++) {
    cin >> a[i];
    a[i] ^= a[i - 1];
  }
  
  int op, x, y, d, r;
  while (q--) {
    cin >> op >> x >> y;
    r = a[x] ^ a[y];
    if (op == 1) {
      cin >> d;
      cout << (d ^ r);
    }
    else cout << r;
    cout << '\n';
  }
}
