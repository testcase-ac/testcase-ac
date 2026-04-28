#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n;
  cin >> n;

  cout << n * n + 1 << '\n';
  for (int i = 1; i <= n; i++) {
    cout << i << ' ' << i << ' ';
    for (int j = i + 2; j <= n; j++) cout << j << ' ' << i << ' ';
  }
  for (int i = n - 1; i >= 1; i--) cout << i << ' ';
  cout << '\n';
}
