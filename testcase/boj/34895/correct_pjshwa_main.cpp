#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 19;
int V[1 << MAXV];

string to_binary(int v) {
  string res;
  while (v) {
    res.push_back((v % 2) + '0');
    v /= 2;
  }
  reverse(res.begin(), res.end());
  return res;
}

void solve() {
  int N; string S; cin >> N >> S;
  for (int i = 0; i < N; ++i) {
    int val = 0;
    for (int j = 0; j < MAXV && i + j < N; ++j) {
      val = 2 * val + (S[i + j] - '0');
      V[val] = 1;
    }
  }
  for (int v = 1;; ++v) {
    if (!V[v]) return cout << to_binary(v) << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
