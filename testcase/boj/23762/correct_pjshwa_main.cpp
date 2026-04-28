#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
pii a[MAX + 1];
int d[4][MAX + 1];

int r(int rem, int i) {
  if (d[rem][i] != -1) return d[rem][i];

  int ret = INF;
  if (i == 0) ret = rem == 0 ? 0 : INF;
  else {
    if (i >= 4) ret = min(ret, r(rem, i - 4) + a[i].first - a[i - 3].first);
    if (rem) ret = min(ret, r(rem - 1, i - 1));
  }
  return d[rem][i] = ret;
}

void trace(int rem, int i) {
  if (i && rem && d[rem - 1][i - 1] == d[rem][i]) {
    cout << a[i].second << '\n';
    trace(rem - 1, i - 1);
  }
  else if (i >= 4) trace(rem, i - 4);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = i - 1;
  sort(a, a + n + 1);
  memset(d, -1, sizeof(d));

  cout << r(n % 4, n) << '\n';
  trace(n % 4, n);
}
