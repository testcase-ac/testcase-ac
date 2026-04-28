#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN + 10];
bool vis[MAXN + 10];
stack<pii> sL[MAXN + 10], sR[MAXN + 10];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  int Q; cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    int L, R, x; cin >> L >> R >> x;
    sL[L].emplace(x, i);
    sR[R + 1].emplace(x, i);
  }

  priority_queue<pii, vector<pii>, greater<>> eff;
  vector<int> lq(N + 1);
  for (int i = 1; i <= N; ++i) {
    while (!sL[i].empty()) {
      auto [x, j] = sL[i].top(); sL[i].pop();
      eff.emplace(x, j);
    }
    while (!sR[i].empty()) {
      auto [x, j] = sR[i].top(); sR[i].pop();
      vis[j] = true;
    }
    while (!eff.empty() && vis[eff.top().second]) eff.pop();

    if (!eff.empty()) {
      auto [x, j] = eff.top();
      if (A[i] > x) lq[i] = j, A[i] = x;
    }
    cout << A[i] << ' ';
  }
  cout << '\n';

  sort(lq.begin() + 1, lq.end()); int lqi = 0;
  for (int i = 1; i <= Q; ++i) {
    while (lqi <= N && lq[lqi] <= i) ++lqi;
    cout << lqi - 1 << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
