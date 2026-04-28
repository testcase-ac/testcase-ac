#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, INF = 0x3f3f3f3f;
pii A[MAX + 10];

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

void solve() {
  int N; cin >> N;

  vector<int> xs;
  map<int, int> miny, maxy;
  int xbound_min = INF, xbound_max = -INF;
  int ybound_min = INF, ybound_max = -INF;
  for (int i = 1; i <= N; i++) {
    int x, y; cin >> x >> y;

    xbound_min = min(xbound_min, x);
    xbound_max = max(xbound_max, x);
    ybound_min = min(ybound_min, y);
    ybound_max = max(ybound_max, y);

    xs.push_back(x);

    if (miny.count(x)) miny[x] = min(miny[x], y);
    else miny[x] = y;

    if (maxy.count(x)) maxy[x] = max(maxy[x], y);
    else maxy[x] = y;
  }
  compress(xs); N = xs.size();

  ll bound = 2LL * (xbound_max - xbound_min + 1) + 2LL * (ybound_max - ybound_min + 1);
  ll area = (ll)(xbound_max - xbound_min + 1) * (ybound_max - ybound_min + 1);
  cout << bound << ' ';

  {
    int cy = INF, py, px;
    for (int i = 1; i <= N; i++) {
      int cx = xs[i - 1];
      cy = min(cy, miny[cx]);

      if (i == 1) area -= (cy - ybound_min);
      else {
        area -= (ll)(cx - px - 1) * (py - ybound_min) + (cy - ybound_min);

        miny[cx] = min(miny[cx], py);
        maxy[cx] = max(maxy[cx], py);
      }

      if (cy == ybound_min) break;
      px = cx, py = cy;
    }
  }
  {
    int cy = INF, py, px;
    for (int i = N; i >= 1; i--) {
      int cx = xs[i - 1];
      cy = min(cy, miny[cx]);

      if (i == N) area -= (cy - ybound_min);
      else {
        area -= (ll)(px - cx - 1) * (py - ybound_min) + (cy - ybound_min);

        miny[cx] = min(miny[cx], py);
        maxy[cx] = max(maxy[cx], py);
      }

      if (cy == ybound_min) break;
      px = cx, py = cy;
    }
  }

  {
    int cy = -INF, py, px;
    for (int i = 1; i <= N; i++) {
      int cx = xs[i - 1];
      cy = max(cy, maxy[cx]);

      if (i == 1) area -= (ybound_max - cy);
      else area -= (ll)(cx - px - 1) * (ybound_max - py) + (ybound_max - cy);

      if (cy == ybound_max) break;
      px = cx, py = cy;
    }
  }
  {
    int cy = -INF, py, px;
    for (int i = N; i >= 1; i--) {
      int cx = xs[i - 1];
      cy = max(cy, maxy[cx]);

      if (i == N) area -= (ybound_max - cy);
      else area -= (ll)(px - cx - 1) * (ybound_max - py) + (ybound_max - cy);

      if (cy == ybound_max) break;
      px = cx, py = cy;
    }
  }
  cout << area << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
