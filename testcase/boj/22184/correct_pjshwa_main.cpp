#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

// returns true if a is a prefix of b
bool is_prefix(string& a, string& b) {
  if (a.size() > b.size()) return false;
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) return false;
  }
  return true;
}

// returns true if a is a suffix of b
bool is_suffix(string& a, string& b) {
  if (a.size() > b.size()) return false;
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[b.size() - a.size() + i]) return false;
  }
  return true;
}

void solve() {
  int L, m; string S1, S2; cin >> L >> m >> S1 >> S2;
  int Z1 = S1.size(), Z2 = S2.size();
  if (Z1 > Z2) swap(Z1, Z2), swap(S1, S2);

  if (Z1 + Z2 <= L) {
    ll v = lpow(26, L - Z1 - Z2, m), d = 0;
    if (is_prefix(S1, S2) && is_suffix(S1, S2)) {
      if (2 * Z2 <= L) d = lpow(26, L - 2 * Z2, m);
      else {
        string S(L, ' '); int ok = 1;
        for (int i = 0; i < Z2; ++i) S[i] = S2[i];
        for (int i = 0; i < Z2; ++i) {
          if (S[L - 1 - i] == ' ') S[L - 1 - i] = S2[Z2 - 1 - i];
          else if (S[L - 1 - i] != S2[Z2 - 1 - i]) ok = 0;
        }
        if (ok) d = 1;
      }
    }

    ll ans = (v + v - d + m) % m;
    cout << ans << '\n';
  } else if (Z1 > L || Z2 > L) {
    cout << "0\n";
  } else {
    string S(L, ' '); int ok1 = 1, ok2 = 1, ok3 = 0;
    for (int i = 0; i < Z1; ++i) S[i] = S1[i];
    for (int i = 0; i < Z2; ++i) {
      if (S[L - 1 - i] == ' ') S[L - 1 - i] = S2[Z2 - 1 - i];
      else if (S[L - 1 - i] != S2[Z2 - 1 - i]) ok1 = 0;
    }

    S = string(L, ' ');
    for (int i = 0; i < Z2; ++i) S[i] = S2[i];
    for (int i = 0; i < Z1; ++i) {
      if (S[L - 1 - i] == ' ') S[L - 1 - i] = S1[Z1 - 1 - i];
      else if (S[L - 1 - i] != S1[Z1 - 1 - i]) ok2 = 0;
    }

    if (is_prefix(S1, S2) && is_suffix(S1, S2)) {
      S = string(L, ' '); ok3 = 1;
      for (int i = 0; i < Z2; ++i) S[i] = S2[i];
      for (int i = 0; i < Z2; ++i) {
        if (S[L - 1 - i] == ' ') S[L - 1 - i] = S2[Z2 - 1 - i];
        else if (S[L - 1 - i] != S2[Z2 - 1 - i]) ok3 = 0;
      }
    }

    cout << ok1 + ok2 - ok3 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
