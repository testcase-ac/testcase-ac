#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
const ll INF = 1e18;
ll cdist[MAX + 1];
int from[MAX + 1];
vector<pll> graph[MAX + 1];

int dirx(string s) {
  if (s == "N") return 0;
  if (s == "NE") return 1;
  if (s == "E") return 2;
  if (s == "SE") return 3;
  if (s == "S") return 4;
  if (s == "SW") return 5;
  if (s == "W") return 6;
  if (s == "NW") return 7;
}

int dirdif(int a, int b) {
  return (b - a + 8) % 8;
}

void dijk(int s) {
  cdist[s] = 0;

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        from[vi] = ui;
        pq.push({cdist[vi], vi});
      }
    }
  }
}

int main() {
  fast_io();

  int n, s, e;
  cin >> n >> s >> e;

  vector<tuple<int, int, int, int, int>> pts;
  for (int i = 0; i < n; i++) {
    int xi, yi, ci;
    string di;
    cin >> xi >> yi >> ci >> di;
    pts.emplace_back(xi, yi, ci, dirx(di), i);
  }

  int sp = s - 1, ep = e - 1;
  fill(cdist, cdist + MAX + 1, INF);

  sort(pts.begin(), pts.end(), [&](auto& a, auto& b) {
    auto [xi, yi, ci, di, oi] = a;
    auto [xj, yj, cj, dj, oj] = b;
    return xi == xj ? yi < yj : xi < xj;
  });
  for (int i = 0; i < n; i++) {
    auto [xi, yi, ci, di, oi] = pts[i];
    if (i > 0) {
      auto [xj, yj, cj, dj, oj] = pts[i - 1];
      if (xi == xj) {
        int f = dirdif(di, dirx("S"));
        graph[oi].emplace_back(oj, ci * f);
      }
    }
    if (i < n - 1) {
      auto [xj, yj, cj, dj, oj] = pts[i + 1];
      if (xi == xj) {
        int f = dirdif(di, dirx("N"));
        graph[oi].emplace_back(oj, ci * f);
      }
    }
  }

  sort(pts.begin(), pts.end(), [&](auto& a, auto& b) {
    auto [xi, yi, ci, di, oi] = a;
    auto [xj, yj, cj, dj, oj] = b;
    return yi == yj ? xi < xj : yi < yj;
  });
  for (int i = 0; i < n; i++) {
    auto [xi, yi, ci, di, oi] = pts[i];
    if (i > 0) {
      auto [xj, yj, cj, dj, oj] = pts[i - 1];
      if (yi == yj) {
        int f = dirdif(di, dirx("W"));
        graph[oi].emplace_back(oj, ci * f);
      }
    }
    if (i < n - 1) {
      auto [xj, yj, cj, dj, oj] = pts[i + 1];
      if (yi == yj) {
        int f = dirdif(di, dirx("E"));
        graph[oi].emplace_back(oj, ci * f);
      }
    }
  }

  sort(pts.begin(), pts.end(), [&](auto& a, auto& b) {
    auto [xi, yi, ci, di, oi] = a;
    auto [xj, yj, cj, dj, oj] = b;
    return yi - xi == yj - xj ? xi < xj : yi - xi < yj - xj;
  });
  for (int i = 0; i < n; i++) {
    auto [xi, yi, ci, di, oi] = pts[i];
    if (i > 0) {
      auto [xj, yj, cj, dj, oj] = pts[i - 1];
      if (yi - xi == yj - xj) {
        int f = dirdif(di, dirx("SW"));
        graph[oi].emplace_back(oj, ci * f);
      }
    }
    if (i < n - 1) {
      auto [xj, yj, cj, dj, oj] = pts[i + 1];
      if (yi - xi == yj - xj) {
        int f = dirdif(di, dirx("NE"));
        graph[oi].emplace_back(oj, ci * f);
      }
    }
  }

  sort(pts.begin(), pts.end(), [&](auto& a, auto& b) {
    auto [xi, yi, ci, di, oi] = a;
    auto [xj, yj, cj, dj, oj] = b;
    return yi + xi == yj + xj ? xi < xj : yi + xi < yj + xj;
  });
  for (int i = 0; i < n; i++) {
    auto [xi, yi, ci, di, oi] = pts[i];
    if (i > 0) {
      auto [xj, yj, cj, dj, oj] = pts[i - 1];
      if (yi + xi == yj + xj) {
        int f = dirdif(di, dirx("NW"));
        graph[oi].emplace_back(oj, ci * f);
      }
    }
    if (i < n - 1) {
      auto [xj, yj, cj, dj, oj] = pts[i + 1];
      if (yi + xi == yj + xj) {
        int f = dirdif(di, dirx("SE"));
        graph[oi].emplace_back(oj, ci * f);
      }
    }
  }

  dijk(sp);
  if (cdist[ep] == INF) cout << "-1\n";
  else {
    stack<int> traj;
    int im = ep;
    while (im != sp) {
      traj.push(im);
      im = from[im];
    }
    traj.push(sp);

    cout << cdist[ep] << '\n';
    while (!traj.empty()) {
      cout << traj.top() + 1 << ' ';
      traj.pop();
    }
    cout << '\n';
  }
}
