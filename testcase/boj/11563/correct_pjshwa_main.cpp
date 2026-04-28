#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const double MAX = 1e12;

double pdist(pair<double, double>& p1, pair<double, double>& p2) {
  double x1, y1, x2, y2;
  tie(x1, y1) = p1;
  tie(x2, y2) = p2;

  return sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
}

// Minimum Distance between a Point and a Line
// http://paulbourke.net/geometry/pointlineplane/
double pldist(pair<double, double>& ls, pair<double, double>& le, pair<double, double>& po) {
  double x1, y1, x2, y2, x3, y3, x, y;
  tie(x1, y1) = ls;
  tie(x2, y2) = le;
  tie(x3, y3) = po;

  double u = (x3 - x1) * (x2 - x1) + (y3 - y1) * (y2 - y1);
  double d = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
  if (d == 0) return MAX;

  u /= d;
  if (u < 0 || u > 1) return MAX;

  x = x1 + u * (x2 - x1);
  y = y1 + u * (y2 - y1);

  return sqrt((y - y3) * (y - y3) + (x - x3) * (x - x3));
}

pair<pair<double, double>, pair<double, double>> ss[2000];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> ss[i].first.first >> ss[i].first.second;
    cin >> ss[i].second.first >> ss[i].second.second;
  }

  double a, b, c, d, mv = MAX;
  for (int i = 0; i < m; i++) {
    cin >> a >> b >> c >> d;
    pair<double, double> p1 = {a, b};
    pair<double, double> p2 = {c, d};

    for (int i = 0; i < n; i++) {
      mv = min(mv, pdist(ss[i].first, p1));
      mv = min(mv, pdist(ss[i].second, p1));
      mv = min(mv, pdist(ss[i].first, p2));
      mv = min(mv, pdist(ss[i].second, p2));
      mv = min(mv, pldist(ss[i].first, ss[i].second, p1));
      mv = min(mv, pldist(ss[i].first, ss[i].second, p2));
      mv = min(mv, pldist(p1, p2, ss[i].first));
      mv = min(mv, pldist(p1, p2, ss[i].second));
    }
  }

  cout << fixed << setprecision(12) << mv;

}
