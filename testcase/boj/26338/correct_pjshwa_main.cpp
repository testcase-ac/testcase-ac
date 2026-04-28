#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int a[MAX + 1], s[MAX + 1];

int tc;
void solve() {
  cout << "Set #" << ++tc << ": ";

  int n; cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  sort(a, a + n);
  s[0] = a[0];
  for (int i = 1; i < n; i++) s[i] = s[i - 1] + a[i];
  a[n] = INF;

  if (a[0] > 1) return cout << "1\n", void();

  for (int i = 1; i <= n; i++) {
    if (a[i] > s[i - 1] + 1) {
      cout << s[i - 1] + 1 << '\n';
      break;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
