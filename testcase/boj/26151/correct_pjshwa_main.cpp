#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const string NATO[26] = {
  "ALFA", "BRAVO", "CHARLIE", "DELTA", "ECHO",
  "FOXTROT", "GOLF", "HOTEL", "INDIA", "JULIETT",
  "KILO", "LIMA", "MIKE", "NOVEMBER", "OSCAR",
  "PAPA", "QUEBEC", "ROMEO", "SIERRA", "TANGO",
  "UNIFORM", "VICTOR", "WHISKEY", "XRAY", "YANKEE",
  "ZULU"
};
const ll MAXL = 60, LIM = 1e18;
ll d[MAXL + 1][26];
vector<ll> P;
string S;

void g(int l) {
  P.clear();
  P.push_back(0);

  for (char c : S) {
    ll x = d[l][c - 'A'];
    x += P.back();
    if (x > LIM) return;
    P.push_back(x);
  }
}

char f(int l, int c, ll x) {
  if (l == 0) {
    // assert(x == 1);
    return c + 'A';
  }

  ll acc = 0;
  for (char o : NATO[c]) {
    acc += d[l - 1][o - 'A'];
    if (acc >= x) return f(l - 1, o - 'A', x - (acc - d[l - 1][o - 'A']));
  }
}

void solve() {
  int Q;
  cin >> S >> Q;

  g(0); ll L = 0;

  // for (int e : P ) cout << e << ' '; cout << endl;

  while (Q--) {
    ll op, x;
    cin >> op >> x;
    if (op == 1) {
      ll preL = L;
      L += x;
      if (L > MAXL) L = MAXL;
      if (preL != L) g(L);
    }
    if (op == 2) {
      auto it = upper_bound(P.begin(), P.end(), x);
      int i = it - P.begin() - 1;

      if (L == 0) cout << S[i - 1];
      else cout << f(L - 1, S[i] - 'A', x - P[i]);
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  fill(d[0], d[0] + 26, 1);
  for (int i = 1; i <= 60; i++) {
    for (int c = 0; c < 26; c++) {
      for (char o : NATO[c]) {
        d[i][c] += d[i - 1][o - 'A'];
        if (d[i][c] > LIM) d[i][c] = LIM + 1;
      }
    }
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
