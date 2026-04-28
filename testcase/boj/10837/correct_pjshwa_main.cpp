#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  while (k--) {
    int a, b;
    cin >> a >> b;
    int ans = abs(a - b) + max(a, b) - n;
    if (a < b) cout << (ans <= 1) << '\n';
    else if (a > b) cout << (ans <= 2) << '\n';
    else cout << "1\n";
  }
}
