#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int v[MAX + 1];

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; i++) cin >> v[i];

  int s = 1, e = 1;
  for (int i = 2; i <= n; i++) {
    if (v[i] < v[i - 1]) {
      s = i;
      while (s > 1 && v[s - 1] >= v[s]) s--;
      break;
    }
  }
  for (int i = n - 1; i >= 1; i--) {
    if (v[i] > v[i + 1]) {
      e = i;
      while (e < n && v[e + 1] <= v[e]) e++;
      break;
    }
  }

  reverse(v + s, v + e + 1);
  for (int i = 2; i <= n; i++) {
    if (v[i] < v[i - 1]) return cout << "impossible\n", void();
  }
  cout << s << ' ' << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
