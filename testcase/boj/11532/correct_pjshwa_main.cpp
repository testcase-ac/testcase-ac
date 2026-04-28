#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct Droplet {
  double x, y, vx, vy, r;

  Droplet merge(Droplet& other) {
    double w = r * r, ow = other.r * other.r;
    double sw = w + ow;

    double nx = (w / sw) * x + (ow / sw) * other.x;
    double ny = (w / sw) * y + (ow / sw) * other.y;
    double nvx = (w / sw) * vx + (ow / sw) * other.vx;
    double nvy = (w / sw) * vy + (ow / sw) * other.vy;
    double nr = sqrt(sw);
    return {nx, ny, nvx, nvy, nr};
  }

  pair<double, bool> collide_time(Droplet& other) {
    double dx = x - other.x;
    double dy = y - other.y;
    double dvx = vx - other.vx;
    double dvy = vy - other.vy;
    double dr = r + other.r;
    double a = dvx * dvx + dvy * dvy;
    double b = 2 * (dx * dvx + dy * dvy);
    double c = dx * dx + dy * dy - dr * dr;
    double d = b * b - 4 * a * c;
    if (d < 0) return {0, false};

    double t1 = (-b + sqrt(d)) / (2 * a);
    double t2 = (-b - sqrt(d)) / (2 * a);
    return {min(t1, t2), true};
  }

  void move(double t) {
    x += vx * t;
    y += vy * t;
  }
};

void solve() {
  int N; cin >> N;
  vector<Droplet> droplets(N);
  for (int i = 0; i < N; ++i) {
    auto& item = droplets[i];
    cin >> item.x >> item.y >> item.vx >> item.vy >> item.r;
  }

  double base = 0;
  while (1) {
    double t = DBL_MAX; int mi, mj;
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
      auto [ct, collides] = droplets[i].collide_time(droplets[j]);
      if (!collides) continue;
      if (ct < t) t = ct, mi = i, mj = j;
    }
    if (t == DBL_MAX) break;

    for (int i = 0; i < N; ++i) droplets[i].move(t);
    auto nd = droplets[mi].merge(droplets[mj]);
    vector<Droplet> next{nd};
    for (int i = 0; i < N; ++i) {
      if (i == mi || i == mj) continue;
      next.push_back(droplets[i]);
    }
    droplets = next;
    base += t;
    --N;
  }

  cout << N << ' ' << fixed << setprecision(10) << base << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
