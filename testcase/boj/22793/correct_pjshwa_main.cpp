#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll n;
void solve() {
  ll mbase = 0, mpow = 1;
  bool minus = false;

  cout << n << " = ";
  if (n == 0) return cout << "0 GSC\n", void();

  if (n < 0) {
    minus = true;
    while (mpow < -n) {
      mbase++;
      mpow *= 3;
    }
    n = mpow + n;
  }

  stack<int> ro, oo;
  while (n) {
    ro.push(n % 3);
    n /= 3;
  }
  while (!ro.empty()) {
    oo.push(ro.top());
    ro.pop();
  }

  string ans = "";
  while (!oo.empty()) {
    bool carry = false;
    if (oo.top() == 0) ans += "0";
    if (oo.top() == 1) ans += "1";
    if (oo.top() == 2) {
      ans += "-";
      carry = true;
    }
    if (oo.top() == 3) {
      ans += "0";
      carry = true;
    }
    oo.pop();
    if (carry) {
      if (oo.empty()) oo.push(1);
      else {
        int t = oo.top();
        oo.pop();
        oo.push(t + 1);
        carry = false;
      }
    }
  }
  if (minus) {
    if (ans.size() == mbase + 1) ans.pop_back();
    else {
      while (ans.size() < mbase) ans += "0";
      ans += '-';
    }
  }
  reverse(ans.begin(), ans.end());
  cout << ans << " GSC\n";
}

int main() {
  fast_io();

  while (cin >> n) solve();
}
