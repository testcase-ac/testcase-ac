#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int a, b;
void solve() {
  cout << a + b << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> a >> b;
    if (a == 0 && b == 0) break;
    solve();
  }
}
