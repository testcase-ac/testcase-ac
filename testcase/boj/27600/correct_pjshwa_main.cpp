#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, q; string s; cin >> n >> s >> q;

  ll plus = 0, minus = 0;
  for (char c : s) {
    if (c == '+') plus++;
    else minus++;
  }

  while (q--) {
    int a, b; cin >> a >> b;
    if (plus == minus) {
      cout << "YES\n";
      continue;
    }
    if (a == b) {
      cout << "NO\n";
      continue;
    }

    ll val1 = plus * a - minus * b;
    ll val2 = plus * b - minus * a;
    if (val1 == 0 || val2 == 0) {
      cout << "YES\n";
      continue;
    }

    int dif1 = a - b, dif2 = b - a;
    bool sgn1 = val1 > 0 == dif1 > 0, sgn2 = val2 > 0 == dif2 > 0;

    if (sgn1 && (val1 % dif1) == 0 && (val1 / dif1) <= plus) cout << "YES\n";
    else if (sgn2 && (val2 % dif2) == 0 && (val2 / dif2) <= plus) cout << "YES\n";
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
