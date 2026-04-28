#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, m;
void solve() {
  if (n + m == 13) cout << "Never speak again.\n";
  else if (n == m) cout << "Undecided.\n";
  else if (n > m) cout << "To the convention.\n";
  else cout << "Left beehind.\n";
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    solve();
  }
}
