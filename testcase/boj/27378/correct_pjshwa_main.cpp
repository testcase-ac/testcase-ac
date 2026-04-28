#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 62;
string O, S;
ll K;
ll d[MAX][MAX][2];

// current digit, remaining diff, following original number
ll r(int i, int rem, bool f) {
  if (i == MAX) return rem == 0;
  if (d[i][rem][f] != -1) return d[i][rem][f];

  ll ret = 0, o = O[i] - '0';
  if (f) {
    int c = S[i] - '0';
    for (int u = 0; u <= c; u++) {
      if (rem - (u != o) < 0) continue;
      ret += r(i + 1, rem - (u != o), u == c);
    }
  }
  else {
    for (int u = 0; u <= 1; u++) {
      if (rem - (u != o) < 0) continue;
      ret += r(i + 1, rem - (u != o), 0);
    }
  }

  return d[i][rem][f] = ret;
}

ll upto(ll n) {
  memset(d, -1, sizeof(d));
  S = bitset<MAX>(n).to_string();
  return r(0, K, 1);
}

void solve() {
  ll N, A, B; cin >> N >> K >> A >> B;
  O = bitset<MAX>(N).to_string();
  cout << upto(B) - upto(A - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
