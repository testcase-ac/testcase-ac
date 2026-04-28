#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  int i = 0;
  while (i < n) {
    cout << a[i] << ' ';
    i += a[i];
  }
}
