#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
int s[10][MAX];
int d[550000];
int n, m;

int solve_day(int day) {
  memset(d, 0, sizeof(d));
  
  for (int w = 0; w <= 500000; w++) {
    for (int i = 0; i < n; i++) d[w + s[day][i]] = max(d[w + s[day][i]], d[w] + s[day + 1][i] - s[day][i]);
  }
  return d[m];
}

void solve() {
  int d;
  cin >> n >> d >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < d; j++) cin >> s[j][i];
  for (int i = 0; i < d - 1; i++) m += solve_day(i);
  cout << m << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
