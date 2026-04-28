#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int Xmin[MAXN], Xmax[MAXN], Ymin[MAXN], Ymax[MAXN];

void solve() {
  int R, C, N; cin >> R >> C >> N;
  memset(Xmax, -1, sizeof(Xmax));
  for (int i = 0; i < N; ++i) {
    int a, v, h; cin >> a >> v >> h; --a;
    if (Xmax[a] == -1) {
      Xmin[a] = Xmax[a] = v;
      Ymin[a] = Ymax[a] = h;
    } else {
      Xmin[a] = min(Xmin[a], v); Xmax[a] = max(Xmax[a], v);
      Ymin[a] = min(Ymin[a], h); Ymax[a] = max(Ymax[a], h);
    }
  }

  ll ansi = -1, answ = 0;
  for (int i = 0; i < N; ++i) {
    if (Xmax[i] == -1) continue;
    ll vw = Xmax[i] - Xmin[i] + 1, hw = Ymax[i] - Ymin[i] + 1;
    if (vw * hw > answ) {
      answ = vw * hw;
      ansi = i;
    }
  }
  cout << ansi + 1 << ' ' << answ << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
