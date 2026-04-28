#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
int c[MAX];
double d[MAX];

int main() {
  fast_io();

  int n;
  double a, b;
  cin >> n >> a >> b;
  for (int i = 0; i < n; i++) cin >> c[i];
  sort(c, c + n);

  d[0] = a;
  for (int i = 1; i < n; i++) {
    d[i] = d[i - 1] + min(a, b * (c[i] - c[i - 1]) / 2);
  }
  cout << setprecision(10) << d[n - 1] << '\n';
}
