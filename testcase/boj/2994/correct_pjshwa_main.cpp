#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;
int a[MAX + 1], d[MAX + 1][5001];

void solve() {
  int T, N;
  cin >> T >> N;
  for (int i = 1; i <= N; i++) cin >> a[i];

  fill(d[0], d[0] + T + 1, -INF);
  d[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    for (int w = 0; w <= T; w++) d[i][w] = d[i - 1][w];
    for (int w = 0; w <= T; w++) {
      if (w >= a[i]) d[i][w] = max(d[i][w], d[i - 1][w - a[i]] + 1);
    }
  }

  int maxW = 0;
  for (int w = 0; w <= T; w++) {
    if (d[N][w] > 0) maxW = w;
  }

  // Trace
  set<int> r;
  int w = maxW;
  for (int i = N; i >= 1; i--) {
    if (w >= a[i] && d[i][w] == d[i - 1][w - a[i]] + 1) {
      r.insert(i);
      w -= a[i];
    }
  }

  vector<int> ans(N + 1);
  int pt1 = 0, pt2 = 0;
  for (int i = 1; i <= N; i++) {
    if (r.count(i)) {
      ans[i] = pt1;
      pt1 += a[i];
    }
    else {
      ans[i] = pt2;
      pt2 += a[i];
    }
  }

  for (int i = 1; i <= N; i++) cout << ans[i] << ' ';
  cout << '\n';  
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
