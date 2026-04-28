#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, C; cin >> N >> C;

  map<int, int> freq, sidx;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    freq[x]++;
    if (sidx.find(x) == sidx.end()) sidx[x] = i;
  }

  vector<tii> A;
  for (auto [x, f] : freq) {
    A.push_back({-f, sidx[x], x});
  }
  sort(A.begin(), A.end());

  for (auto [f, _, x] : A) {
    for (int i = 0; i < -f; i++) {
      cout << x << ' ';
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
