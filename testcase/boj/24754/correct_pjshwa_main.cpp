#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e5;
int a[MAX + 1], b[MAX + 1];
map<int, int> u;
int ucnt = 0;

void add(int x, int addend) {
  if (u[x] == 0) ucnt++;
  u[x] += addend;
  if (u[x] == 0) ucnt--;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];

  for (int i = 1; i <= n; i++) {
    add(a[i], 1);
    add(b[i], -1);

    cout << b[i] << ' ';
    if (i < n && ucnt == 0) cout << "# ";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
