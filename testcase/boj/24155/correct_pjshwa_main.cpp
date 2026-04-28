#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], s2r[101];

void solve() {
  int n;
  cin >> n;

  map<int, int> u;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    u[-a[i]]++;
  }

  int cr = 1;
  for (auto [k, v] : u) {
    s2r[-k] = cr;
    cr += v;
  }

  for (int i = 0; i < n; i++) cout << s2r[a[i]] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
