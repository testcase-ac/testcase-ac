#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Scenario #" << ++tc << ":\n";

  int N; cin >> N;
  vector<tii> A(N);
  for (int i = 0; i < N; i++) {
    int d, s, e; cin >> d >> s >> e;
    A[i] = {d, s, e};
  }
  sort(A.begin(), A.end(), [](tii a, tii b) {
    auto [ad, as, ae] = a; auto [bd, bs, be] = b;
    if (ad != bd) return ad < bd;
    if (ae != be) return ae < be;
    return as < bs;
  });

  int ans = 0, ld = 0, le = 0;
  for (auto& [d, s, e] : A) {
    if (d != ld) {
      ans++;
      ld = d;
      le = e;
    }
    else {
      if (s < le) continue;
      ans++;
      le = e;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
