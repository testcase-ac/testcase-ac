#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k, q; cin >> n >> k >> q;

  vector<tuple<int, int, int>> Q;
  for (int i = 0; i < q; ++i) {
    int p, l, r; cin >> p >> l >> r;
    Q.emplace_back(l, -1, i);
    Q.emplace_back(r, 1, i);
  }
  sort(Q.begin(), Q.end());

  int cnt = n; vector<int> ans(q);
  for (auto& [_, o, i] : Q) {
    cnt += o;
    if (o == 1 && cnt == 1) ans[i] = 1;
  }

  int ck = k;
  for (auto& [_, o, i] : Q) {
    if (o == -1 && ans[i]) --ck;
    if (ck < 0) return cout << "impossible\n", void();
    if (o == 1 && ans[i]) ++ck;
  }
  assert(ck == k);

  for (int i = 0; i < q; ++i) cout << ans[i];
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
