#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int d[MAXN + 1];
vector<int> pr;

void solve() {
  int N, MOD;
  cin >> N >> MOD;

  d[0] = 1;
  for (int p : pr) for (int i = p; i <= N; i++) {
    d[i] = (d[i] + d[i - p]) % MOD;
  }
  cout << d[N] << '\n';
}

int main() {
  fast_io();

  for (int i = 1; i <= MAXN; i++) {
    string s = to_string(i);
    int acc = 0;
    for (char c : s) acc += c - '0';
    if (i % acc == 0) pr.push_back(i);
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
