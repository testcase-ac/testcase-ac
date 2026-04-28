#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int a[MAX];

int main() {
  fast_io();

  int n, x, y;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  cin >> x >> y;

  int z = 0;
  for (int i = 0; i < n; i++) if (a[i] >= y) z++;

  cout << n * x / 100 << ' ' << z << '\n';
}
