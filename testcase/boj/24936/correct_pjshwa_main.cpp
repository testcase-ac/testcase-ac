#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n;
  cin >> n;

  int sum = 0;
  for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];

  set<int> u;
  for (int i = 0; i < n; i++) u.insert(sum - a[i]);

  cout << u.size() << '\n';
  for (int e : u) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
