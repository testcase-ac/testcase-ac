#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll d2c[100];

string r(ll K) {
  if (K == 0) return "";
  if (K == 1) return "0";
  if (K == 2) return "1";
  if (K == 3) return "10";

  int i = 0;
  while (d2c[i] < K) i++;
  i--;

  string prev = r(K - d2c[i]);
  reverse(prev.begin(), prev.end());
  while (prev.size() < max(0, i - 1)) prev += "0";
  reverse(prev.begin(), prev.end());

  return "10" + prev;
}

void solve() {
  ll K;
  cin >> K;
  cout << r(K + 1) << '\n';
}

int main() {
  fast_io();

  for (int i = 0; i < 3; i++) d2c[i] = i + 1;
  for (int i = 3; i <= 88; i++) {
    d2c[i] = d2c[i - 1] + d2c[i - 2];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
