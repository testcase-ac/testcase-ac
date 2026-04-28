#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int score(int a, int b) {
  int v = a * b, ret = 0;
  for (char c : to_string(v)) ret += c - '0';
  return ret;
}

void solve() {
  int N;
  cin >> N;

  map<int, int> t;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    t[x]++;
  }

  int ans = 0;
  for (int i = 1; i <= 999; i++) {
    if (!t.count(i)) continue;

    if (t[i] >= 2) ans = max(ans, score(i, i));
    for (auto& [k, v] : t) {
      if (i == k) continue;
      ans = max(ans, score(i, k));
    }
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
