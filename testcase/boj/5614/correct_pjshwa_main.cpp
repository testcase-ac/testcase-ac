#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  map<string, int> t;
  for (int i = 0; i < N; i++) {
    string S; int W;
    cin >> S >> W;
    t[S] += W;
  }

  vector<pair<string, int>> v;
  for (auto [S, W] : t) {
    v.emplace_back(S, W);
  }
  sort(v.begin(), v.end(), [&](auto &a, auto &b) {
    auto [S1, W1] = a; auto [S2, W2] = b;
    if (S1.size() == S2.size()) return S1 < S2;
    return S1.size() < S2.size();
  });

  for (auto [S, W] : v) {
    cout << S << ' ' << W << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
