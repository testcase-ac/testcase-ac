#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXL = 3e5, MOD = 1e9 + 7;
ll S[MAXL];

void add_to(int l, int val) {
  if (S[l] == -1) S[l] = val;
  else S[l] = (S[l] + val) % MOD;
}

void mul_to(int l, int val) {
  if (S[l] == -1) S[l] = val;
  else S[l] = (S[l] * val) % MOD;
}

void solve() {
  ll N, l = 0; cin >> N;
  memset(S, -1, sizeof(S));

  for (int i = 0; i < N; ++i) {
    string T; cin >> T;
    if (T == "(") ++l;
    else if (T == ")") {
      int nl = l - 1;
      if (l & 1) add_to(nl, S[l]);
      else mul_to(nl, S[l]);
      S[l] = -1; l = nl;
    }
    else {
      int x = stoi(T);
      if (l & 1) mul_to(l, x);
      else add_to(l, x);
    }
  }

  cout << S[0] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
