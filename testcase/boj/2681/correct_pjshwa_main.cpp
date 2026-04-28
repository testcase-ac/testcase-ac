#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pdd = pair<double, double>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

pdd get_intersection_point(pdd p1, pdd p2, pdd p3, pdd p4) {
  auto [x1, y1] = p1; auto [x2, y2] = p2; auto [x3, y3] = p3; auto [x4, y4] = p4;
  double A1 = x2 - x1, B1 = y2 - y1, A2 = x4 - x3, B2 = y4 - y3;
  double det = A1 * B2 - A2 * B1;
  assert(det != 0);

  double t1 = (B2 * (x3 - x1) - A2 * (y3 - y1)) / det;
  return {x1 + t1 * A1, y1 + t1 * B1};
}

double tri_area(pdd p1, pdd p2, pdd p3) {
  auto [x1, y1] = p1; auto [x2, y2] = p2; auto [x3, y3] = p3;
  return abs(x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2) / 2;
}

double euc_dist(pdd p1, pdd p2) {
  auto [x1, y1] = p1; auto [x2, y2] = p2;
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void solve() {
  double Ax = 0, Ay = 0, Bx, By = 0, Cx, Cy, Dx, Dy; cin >> Bx >> Cx >> Cy >> Dx >> Dy;

  double Apx = (Bx + Cx) / 2, Apy = (By + Cy) / 2;
  double Bpx = (Cx + Dx) / 2, Bpy = (Cy + Dy) / 2;
  double Cpx = (Dx + Ax) / 2, Cpy = (Dy + Ay) / 2;
  double Dpx = (Ax + Bx) / 2, Dpy = (Ay + By) / 2;

  auto [Acx, Acy] = get_intersection_point({Ax, Ay}, {Apx, Apy}, {Bx, By}, {Bpx, Bpy});
  auto [Bcx, Bcy] = get_intersection_point({Bx, By}, {Bpx, Bpy}, {Cx, Cy}, {Cpx, Cpy});
  auto [Ccx, Ccy] = get_intersection_point({Cx, Cy}, {Cpx, Cpy}, {Dx, Dy}, {Dpx, Dpy});
  auto [Dcx, Dcy] = get_intersection_point({Dx, Dy}, {Dpx, Dpy}, {Ax, Ay}, {Apx, Apy});

  cout << fixed << setprecision(3) <<
    tri_area({Ax, Ay}, {Bx, By}, {Acx, Acy}) << ' ' <<
    tri_area({Bx, By}, {Cx, Cy}, {Bcx, Bcy}) << ' ' <<
    tri_area({Cx, Cy}, {Dx, Dy}, {Ccx, Ccy}) << ' ' <<
    tri_area({Dx, Dy}, {Ax, Ay}, {Dcx, Dcy}) << ' ' <<
    tri_area({Acx, Acy}, {Bcx, Bcy}, {Ccx, Ccy}) +
    tri_area({Ccx, Ccy}, {Dcx, Dcy}, {Acx, Acy});

  double mid_len = euc_dist({Acx, Acy}, {Bcx, Bcy}) + euc_dist({Bcx, Bcy}, {Ccx, Ccy}) +
    euc_dist({Ccx, Ccy}, {Dcx, Dcy}) + euc_dist({Dcx, Dcy}, {Acx, Acy});
  cout << fixed << setprecision(0) << ' ' << ceil(mid_len) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
