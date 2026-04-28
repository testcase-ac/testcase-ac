#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[10000];
int main() {
  fast_io();

  int n, s = 0;
  long long c = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], s += a[i];

  for (int i = 0; i < n; i++) {
    int l = 0;
    for (int j = 0; j < n; j++) {
      l += a[(i + j) % n];
      if (l < 0) c += ((-l - 1) / s + 1);
    }
  }

  cout << c;
}
