#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int k[MAXN];

void solve() {
  int N; cin >> N;

  vector<int> pos, neg;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (x > 0) pos.push_back(x);
    else neg.push_back(-x);
  }
  sort(pos.begin(), pos.end());
  sort(neg.begin(), neg.end());

  vector<int> ans;
  int cur = pos.size(), pos_p = 0, neg_p = 0;
  for (int k = 0; k <= N; ++k) {
    while (pos_p < pos.size() && pos[pos_p] <= k) {
      --cur;
      ++pos_p;
    }

    if (cur == k) ans.push_back(k);

    while (neg_p < neg.size() && neg[neg_p] <= k) {
      ++cur;
      ++neg_p;
    }
  }

  cout << ans.size() << '\n';
  for (int x : ans) cout << x << ' ';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
