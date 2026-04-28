#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, c, k;
  cin >> n;

  int mv = 1e9;
  for (int i = 0; i < n; i++) {
    cin >> c >> k;
    mv = min(mv, k / c);
  }
  cout << mv << '\n';
}
