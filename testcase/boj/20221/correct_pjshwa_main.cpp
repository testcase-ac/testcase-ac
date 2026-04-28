#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  vector<ll> c{0};

  for (int i = 0; i < n; i++) {
    string x;
    cin >> x;
    for (int j = 0; j < x.size(); j++) if (x[j] == '6') x[j] = '9';

    for (int j = 0; j < x.size(); j++) {
      if (x[j] == '9') {
        x[j] = '6';
        if (stoll(x) < c.back()) x[j] = '9';
      }
    }

    if (stoll(x) >= c.back()) c.push_back(stoll(x));
    else return cout << "impossible\n", void();
  }

  cout << "possible\n";
  for (int i = 1; i < c.size(); i++) cout << c[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
