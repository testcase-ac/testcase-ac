#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1500;
int a[MAX][MAX], rc[MAX], cc[MAX];
int r[MAX * MAX + 1], c[MAX * MAX + 1];

void solve() {
  int n;
  cin >> n;

  vector<pair<int, pii>> A;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> a[i][j];
    A.emplace_back(a[i][j], pii(i, j));
  }
  sort(A.begin(), A.end());

  for (auto [v, p] : A) {
    auto [i, j] = p;

    r[v] = rc[i];
    c[v] = cc[j];

    rc[i]++;
    cc[j]++;
  }

  ll ans = 0;
  for (int i = 1; i <= n * n; i++) {
    ans += r[i] * (n - 1 - c[i]);
    ans += c[i] * (n - 1 - r[i]);
  }
  cout << ans / 2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
