#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, T, w, m;
  cin >> n >> T >> w;

  queue<pii> bqueue;
  for (int i = 0; i < n; i++) {
    int px, tx;
    cin >> px >> tx;
    bqueue.push({px, tx});
  }
  cin >> m;
  vector<tii> after_open(m);
  for (int i = 0; i < m; i++) {
    int px, tx, cx;
    cin >> px >> tx >> cx;
    after_open[i] = {cx, px, tx};
  }
  sort(after_open.begin(), after_open.end());

  int ptime = 0, oi = 0;
  for (int t = 0; t < w; t++) {
    while (oi < m && get<0>(after_open[oi]) == t) {
      bqueue.push({get<1>(after_open[oi]), get<2>(after_open[oi])});
      oi++;
    }

    if (ptime == bqueue.front().second) {
      bqueue.pop();
      ptime = 0;
    }

    if (ptime == T) {
      auto [cpx, ctx] = bqueue.front();
      bqueue.push({cpx, ctx - T});
      bqueue.pop();
      ptime = 0;
    }

    cout << bqueue.front().first << '\n';
    ptime++;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
