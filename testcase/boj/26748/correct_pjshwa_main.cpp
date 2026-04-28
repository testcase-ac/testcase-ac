#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll nC2(ll n) {
  return n * (n - 1) / 2;
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  vector<pii> chunks;
  chunks.emplace_back(-1, 0);
  for (int i = 0; i < N; ++i) {
    if (i < N - 1 && S[i] == S[i + 1]) {
      chunks.emplace_back(i, i + 1);
    }
    else if (i < N - 2 && S[i] == S[i + 2]) {
      chunks.emplace_back(i, i + 2);
    }
  }
  chunks.emplace_back(N - 1, N);

  int Z = chunks.size();
  vector<pii> ranges;
  for (int i = 1; i < Z; ++i) {
    auto [ps, pe] = chunks[i - 1]; auto [cs, ce] = chunks[i];
    ranges.emplace_back(ps + 1, ce - 1);
  }

  ll ans = 0;
  for (auto [s, e] : ranges) ans += nC2(e - s + 2);
  for (int i = 1; i < ranges.size(); ++i) {
    auto [ps, pe] = ranges[i - 1]; auto [cs, ce] = ranges[i];
    if (pe == cs) ans--;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
