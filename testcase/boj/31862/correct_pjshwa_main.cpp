#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int W[MAXN + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;
  vector<pii> wait;
  while (M--) {
    int o1, o2, r; cin >> o1 >> o2 >> r;
    if (r == 0) wait.emplace_back(o1, o2);
    else r == 1 ? ++W[o1] : ++W[o2];
  }

  int wi = -1, wx = 0;
  for (int i = 1; i <= N; ++i) {
    if ((i == K && W[i] > wx) || (i != K && W[i] >= wx)) {
      wx = W[i];
      wi = i;
    }
  }

  int Z = wait.size(), ans = 0;
  for (int s = 0; s < (1 << Z); ++s) {
    int cwi = wi, cwx = wx;
    for (int j = 0; j < Z; ++j) {
      auto& [o1, o2] = wait[j];
      if (s & (1 << j)) {
        ++W[o1];
        if (o1 == K && W[o1] > cwx) cwx = W[o1], cwi = o1;
        else if (o1 != K && W[o1] >= cwx) cwx = W[o1], cwi = o1;
      }
      else {
        ++W[o2];
        if (o2 == K && W[o2] > cwx) cwx = W[o2], cwi = o2;
        else if (o2 != K && W[o2] >= cwx) cwx = W[o2], cwi = o2;
      }
    }

    if (cwi == K) ++ans;

    for (int j = 0; j < Z; ++j) {
      auto& [o1, o2] = wait[j];
      if (s & (1 << j)) --W[o1];
      else --W[o2];
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
