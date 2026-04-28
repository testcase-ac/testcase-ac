#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pdd = pair<double, double>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1004;
int parent[MAX];
int XL, YL;

int Find(int x) {
  if (x != parent[x]) parent[x] = Find(parent[x]);
  return parent[x];
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

bool check_validity(double r, vector<pdd>& v) {
  int N = v.size();
  iota(parent, parent + N + 4, 0);

  for (int i = 0; i < N; ++i) {
    int ui = i + 4;
    auto [x, y] = v[i];

    if (x - r < 0) Union(0, ui);
    if (x + r > XL) Union(1, ui);
    if (y - r < 0) Union(3, ui);
    if (y + r > YL) Union(2, ui);
  }

  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      auto [x1, y1] = v[i];
      auto [x2, y2] = v[j];
      double dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

      int ui = i + 4, uj = j + 4;
      if (dist < 2 * r) Union(ui, uj);
    }
  }

  if (Find(0) == Find(3) || Find(2) == Find(1)) return false;
  if (Find(0) == Find(1) || Find(2) == Find(3)) return false;
  return true;
}

void solve() {
  int N; cin >> XL >> YL >> N;
  vector<pdd> v(N);
  for (int i = 0; i < N; ++i) {
    cin >> v[i].first >> v[i].second;
  }

  double left = 0, right = 1e6;
  for (int iter = 0; iter < 100; ++iter) {
    double mid = (left + right) / 2;
    if (check_validity(mid, v)) left = mid;
    else right = mid;
  }
  cout << fixed << setprecision(10) << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
