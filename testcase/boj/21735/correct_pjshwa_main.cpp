#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int n;
int a[101];
int r(int mass, int pos, int m) {
  if (m == 0) return mass;

  int mv = mass;
  if (pos + 1 <= n) mv = max(mv, r(mass + a[pos + 1], pos + 1, m - 1));
  if (pos + 2 <= n) mv = max(mv, r(mass / 2 + a[pos + 2], pos + 2, m - 1));
  return mv;
}

int main() {
  fast_io();

  int m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];

  cout << r(1, 0, m);
}
