#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000;
int a[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];

  for (int i = 0; i < N; i++) {
    int r = N - a[i] + 1;
    if (a[i] > r && (i == 0 || a[i - 1] <= r)) a[i] = r;
    if (a[i] < r && i > 0 && a[i - 1] > a[i]) a[i] = r;
  }

  for (int i = 1; i < N; i++) {
    if (a[i] < a[i - 1]) return cout << "NO\n", void();
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
