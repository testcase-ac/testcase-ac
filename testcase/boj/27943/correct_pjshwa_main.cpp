#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string ask(ll x) {
  cout << "? " << x << endl;
  string ret; cin >> ret;
  return ret;
}

void solve() {
  ll n; cin >> n;

  // Always gaji
  string G = ask((n + 1) / 2);
  ll L, R;

  {
    ll l = 1, r = (n + 1) / 2 + 1;
    while (l < r) {
      ll m = (l + r) / 2;
      string res = ask(m);
      if (res == G) r = m;
      else l = m + 1;
    }
    L = l;
  }
  {
    ll l = (n + 1) / 2, r = n + 1;
    while (l < r) {
      ll m = (l + r) / 2;
      string res = ask(m);
      if (res == G) l = m + 1;
      else r = m;
    }
    R = l - 1;
  }

  cout << "! " << L << ' ' << R << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
