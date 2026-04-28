#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5 + 10;
int dt[MAX];
ll pf[MAX];

int main() {
  fast_io();

  int n, t;
  cin >> n >> t;

  for (int i = 1; i <= n; i++) {
    int k;
    cin >> k;
    for (int j = 1; j <= k; j++) {
      int si, ei;
      cin >> si >> ei;
      dt[si]++;
      dt[ei]--;
    }
  }

  pf[0] = dt[0];
  for (int i = 1; i < MAX; i++) {
    pf[i] = pf[i - 1] + dt[i];
  }

  ll ans = 0, cur = 0;
  int st = 0;
  for (int i = 0; i < t; i++) {
    cur += pf[i];
  }
  ans = max(ans, cur);

  for (int i = t; i < MAX; i++) {
    cur += pf[i];
    cur -= pf[i - t];
    if (cur > ans) {
      ans = cur;
      st = i - t + 1;
    }
  }

  cout << st << ' ' << st + t << '\n';
}
