#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, m;
  cin >> n >> m;

  int l1, r1, l2, r2;
  cin >> l1 >> r1 >> l2 >> r2;

  int B = 0, P = 0, V = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;

    if (l1 <= x && x <= r1) {
      if (l2 <= x && x <= r2) B++;
      else P++;
    }
    else if (l2 <= x && x <= r2) V++;
  }

  int Pc = 0, Vc = 0;
  for (int i = 0; i < m; i++) {
    if (i & 1) {
      if (B) B--, Vc++;
      else if (V) V--, Vc++;
    }
    else {
      if (B) B--, Pc++;
      else if (P) P--, Pc++;
    }
  }

  if (Pc == Vc) cout << "Draw\n";
  else if (Pc > Vc) cout << "Petya\n";
  else cout << "Vasya\n";
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
