#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX + 1];

void solve() {
  int q, m;
  cin >> q >> m;

  int fi = 1, fj = 0, it = 1;
  map<int, int> c;
  int v = fi * m + fj;
  while (!c.count(v)) {
    a[it] = (fi + fj) % m;
    c[v] = it;
    it++;

    int tmp = fj;
    fj = (fi + fj) % m;
    fi = tmp;
    v = fi * m + fj;
  }

  int cstart = c[v], csize = it - cstart;

  string u = " ";
  int ssize = 0;
  for (int i = 1; i < cstart; i++) u += to_string(a[i]);
  int sstart = u.size();
  for (int i = cstart; i < cstart + csize; i++) {
    string as = to_string(a[i]);
    u += as;
    ssize += as.size();
  }

  while (q--) {
    ll n;
    cin >> n;
    if (n < sstart) cout << u[n] << '\n';
    else cout << u[sstart + (n - sstart) % ssize] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
