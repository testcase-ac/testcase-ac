#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int a1[MAX + 1], a2[MAX + 1], p1[MAX + 1], p2[MAX + 1], d1[MAX + 1], d2[MAX + 1];

void solve() {
  int n, s1, s2;
  cin >> n;
  
  fill(d1, d1 + n + 1, INF);
  fill(d2, d2 + n + 1, INF);
  cin >> d1[1] >> d2[1] >> s1 >> s2;
  for (int i = 2; i <= n; i++) cin >> p1[i];
  for (int i = 2; i <= n; i++) cin >> a1[i];
  for (int i = 2; i <= n; i++) cin >> p2[i];
  for (int i = 2; i <= n; i++) cin >> a2[i];

  for (int i = 2; i <= n; i++) {
    d1[i] = min(d1[i - 1] + a1[i], d2[i - 1] + p2[i]);
    d2[i] = min(d2[i - 1] + a2[i], d1[i - 1] + p1[i]);
  }
  cout << min(d1[n] + s1, d2[n] + s2) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
