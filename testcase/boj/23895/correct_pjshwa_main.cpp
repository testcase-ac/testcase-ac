#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];
int tc;

void solve() {
  int n, b;
  cin >> n >> b;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  cout << "Case #" << ++tc << ": ";

  ll sum = 0;
  for (int i = 0; i < n; i++) {
    sum += a[i];
    if (sum > b) return cout << i << '\n', void();
  }
  cout << n << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
