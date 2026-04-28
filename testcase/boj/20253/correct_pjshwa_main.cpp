#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MOD = 1e9 + 7;

void solve() {
  int n;
  cin >> n;

  vector<ll> pos, neg;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x >= 0) pos.push_back(x);
    else neg.push_back(x);
  }
  sort(pos.begin(), pos.end());
  sort(neg.begin(), neg.end());

  ll mval = 0, xval = 0;
  if (pos.size() && neg.size()) {
    for (int i = 0; i < pos.size(); i++) {
      mval = (mval + pos[i] * neg[0]) % MOD;
    }
    for (int i = 1; i < neg.size(); i++) {
      mval = (mval + pos[pos.size() - 1] * neg[i]) % MOD;
    }

    for (int i = 1; i < neg.size(); i++) {
      xval = (xval + neg[0] * neg[i]) % MOD;
    }
    for (int i = 0; i < pos.size() - 1; i++) {
      xval = (xval + pos[i] * pos[pos.size() - 1]) % MOD;
    }
    xval = (xval + neg[neg.size() - 1] * pos[0]) % MOD;
  }
  else if (pos.size()) {
    for (int i = 1; i < pos.size(); i++) {
      mval = (mval + pos[i] * pos[0]) % MOD;
    }
    for (int i = 0; i < pos.size() - 1; i++) {
      xval = (xval + pos[i] * pos[pos.size() - 1]) % MOD;
    }
  }
  else {
    for (int i = 0; i < neg.size() - 1; i++) {
      mval = (mval + neg[i] * neg[neg.size() - 1]) % MOD;
    }
    for (int i = 1; i < neg.size(); i++) {
      xval = (xval + neg[i] * neg[0]) % MOD;
    }
  }

  if (mval < 0) mval += MOD;
  if (xval < 0) xval += MOD;
  cout << mval << ' ' << xval << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
