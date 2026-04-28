#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<pair<tii, tii>, double> d;
int D, S;

double r(tii e, tii p) {
  if (d.count({e, p})) return d[{e, p}];

  auto [e1, e2, e3, e4, e5] = e;
  auto [p1, p2, p3, p4, p5] = p;

  int ecnt = 0, esum = 0, pcnt = 0, psum = 0;
  for (int e : {e1, e2, e3, e4, e5}) {
    if (e == 0) continue;
    ecnt++;
    esum += e;
  }
  for (int p : {p1, p2, p3, p4, p5}) {
    if (p == 0) continue;
    pcnt++;
    psum += p;
  }
  if (ecnt == 0) return 1;
  if (S - (esum + psum) >= D) return 0;

  double prob = 1.0 / (ecnt + pcnt), ret = 0;
  if (e1) {
    vector<int> ev;
    ev.push_back(get<0>(e) - 1);
    ev.push_back(get<1>(e));
    ev.push_back(get<2>(e));
    ev.push_back(get<3>(e));
    ev.push_back(get<4>(e));
    sort(ev.begin(), ev.end());
    ret += prob * r({ev[0], ev[1], ev[2], ev[3], ev[4]}, p);
  }
  if (e2) {
    vector<int> ev;
    ev.push_back(get<0>(e));
    ev.push_back(get<1>(e) - 1);
    ev.push_back(get<2>(e));
    ev.push_back(get<3>(e));
    ev.push_back(get<4>(e));
    sort(ev.begin(), ev.end());
    ret += prob * r({ev[0], ev[1], ev[2], ev[3], ev[4]}, p);
  }
  if (e3) {
    vector<int> ev;
    ev.push_back(get<0>(e));
    ev.push_back(get<1>(e));
    ev.push_back(get<2>(e) - 1);
    ev.push_back(get<3>(e));
    ev.push_back(get<4>(e));
    sort(ev.begin(), ev.end());
    ret += prob * r({ev[0], ev[1], ev[2], ev[3], ev[4]}, p);
  }
  if (e4) {
    vector<int> ev;
    ev.push_back(get<0>(e));
    ev.push_back(get<1>(e));
    ev.push_back(get<2>(e));
    ev.push_back(get<3>(e) - 1);
    ev.push_back(get<4>(e));
    sort(ev.begin(), ev.end());
    ret += prob * r({ev[0], ev[1], ev[2], ev[3], ev[4]}, p);
  }
  if (e5) {
    vector<int> ev;
    ev.push_back(get<0>(e));
    ev.push_back(get<1>(e));
    ev.push_back(get<2>(e));
    ev.push_back(get<3>(e));
    ev.push_back(get<4>(e) - 1);
    sort(ev.begin(), ev.end());
    ret += prob * r({ev[0], ev[1], ev[2], ev[3], ev[4]}, p);
  }
  if (p1) {
    vector<int> pv;
    pv.push_back(get<0>(p) - 1);
    pv.push_back(get<1>(p));
    pv.push_back(get<2>(p));
    pv.push_back(get<3>(p));
    pv.push_back(get<4>(p));
    sort(pv.begin(), pv.end());
    ret += prob * r(e, {pv[0], pv[1], pv[2], pv[3], pv[4]});
  }
  if (p2) {
    vector<int> pv;
    pv.push_back(get<0>(p));
    pv.push_back(get<1>(p) - 1);
    pv.push_back(get<2>(p));
    pv.push_back(get<3>(p));
    pv.push_back(get<4>(p));
    sort(pv.begin(), pv.end());
    ret += prob * r(e, {pv[0], pv[1], pv[2], pv[3], pv[4]});
  }
  if (p3) {
    vector<int> pv;
    pv.push_back(get<0>(p));
    pv.push_back(get<1>(p));
    pv.push_back(get<2>(p) - 1);
    pv.push_back(get<3>(p));
    pv.push_back(get<4>(p));
    sort(pv.begin(), pv.end());
    ret += prob * r(e, {pv[0], pv[1], pv[2], pv[3], pv[4]});
  }
  if (p4) {
    vector<int> pv;
    pv.push_back(get<0>(p));
    pv.push_back(get<1>(p));
    pv.push_back(get<2>(p));
    pv.push_back(get<3>(p) - 1);
    pv.push_back(get<4>(p));
    sort(pv.begin(), pv.end());
    ret += prob * r(e, {pv[0], pv[1], pv[2], pv[3], pv[4]});
  }
  if (p5) {
    vector<int> pv;
    pv.push_back(get<0>(p));
    pv.push_back(get<1>(p));
    pv.push_back(get<2>(p));
    pv.push_back(get<3>(p));
    pv.push_back(get<4>(p) - 1);
    sort(pv.begin(), pv.end());
    ret += prob * r(e, {pv[0], pv[1], pv[2], pv[3], pv[4]});
  }

  return d[{e, p}] = ret;
}

void solve() {
  int n, m, x;
  cin >> n >> m >> D;
  vector<int> a(5), b(5);
  for (int i = 0; i < n; i++) cin >> a[i], S += a[i];
  for (int i = 0; i < m; i++) cin >> b[i], S += b[i];
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  cout << fixed << setprecision(10) << r({b[0], b[1], b[2], b[3], b[4]}, {a[0], a[1], a[2], a[3], a[4]}) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
