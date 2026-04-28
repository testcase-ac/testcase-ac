#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1422;
int a[MAX];

int n;
void solve() {
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  bool f = true;
  for (int i = 1; i < n; i++) {
    if (a[i] - a[i - 1] > 200) f = false;
  }
  if (1422 - a[n - 1] > 100) f = false;

  if (f) cout << "POSSIBLE\n";
  else cout << "IMPOSSIBLE\n";
}

int main() {
  fast_io();

  while (cin >> n) {
    if (n == 0) break;
    solve();
  }
}
