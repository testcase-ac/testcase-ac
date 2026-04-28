#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int p[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int xi, yi;
    cin >> xi >> yi;

    int s = max(0, i - xi - 1);
    p[i] = p[i - 1];
    if (p[i - 1] - p[s] >= yi) p[i]++;
  }
  cout << p[n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
