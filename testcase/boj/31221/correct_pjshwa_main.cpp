#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ask(ll a, ll b) {
  cout << "? " << a << " " << b << endl;
  string res; cin >> res;
  if (res == "+") return 1;
  else if (res == "-") return -1;
  else return 0;
}

void answer(ll x) {
  cout << "! " << x << endl;
}

void solve() {
  ll a, b;
  {
    int l = 0, r = 1e9 + 1;
    while (l < r) {
      ll m = (l + r) / 2;
      int ret = ask(0, m);
      if (ret == 0) return answer(m * m);
      else if (ret == 1) l = m + 1;
      else r = m;
    }
    b = l - 1;
  }
  {
    if (b <= 15) {
      a = 0;
      while (ask(a, b) == 1) a++;
      return answer(a + b * b);
    }
    else {
      ll l = 0, r = 2 * b + 1;
      while (l < r) {
        ll m = (l + r) / 2;
        int ret = ask(m, b);
        if (ret == 0) return answer(m + b * b);
        else if (ret == 1) l = m + 1;
        else r = m;
      }
    }
  }
}

int main() {
  // fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
