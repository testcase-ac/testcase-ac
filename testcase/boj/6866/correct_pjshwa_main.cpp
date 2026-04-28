#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// source: https://stackoverflow.com/questions/2062286/testing-whether-a-line-segment-intersects-a-sphere


struct Vector3 {
  double x, y, z;

  Vector3 operator-(const Vector3& other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  Vector3 operator+(const Vector3& other) const {
    return {x + other.x, y + other.y, z + other.z};
  }

  Vector3 operator*(double scalar) const {
    return {x * scalar, y * scalar, z * scalar};
  }

  double dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
  }
};

bool intersectLineSphere(const Vector3& p0, const Vector3& p1, const Vector3& center, double radius) {
  Vector3 d = p1 - p0;
  Vector3 f = p0 - center;

  double a = d.dot(d);
  double b = 2.0 * f.dot(d);
  double c = f.dot(f) - radius * radius;

  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) return false;

  discriminant = std::sqrt(discriminant);
  double t1 = (-b - discriminant) / (2 * a);
  double t2 = (-b + discriminant) / (2 * a);
  return (t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1);
}

void solve() {
  int xa, ya, za, xb, yb, zb; cin >> xa >> ya >> za >> xb >> yb >> zb;
  Vector3 p0 = {xa, ya, za}, p1 = {xb, yb, zb};

  int N, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) {
    int xc, yc, zc, r; cin >> xc >> yc >> zc >> r;
    Vector3 center = {xc, yc, zc};
    if (intersectLineSphere(p0, p1, center, r)) ++ans;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
