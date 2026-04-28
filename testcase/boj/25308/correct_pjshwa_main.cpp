#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
};

double cross_product(Point p1, Point p2, Point p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

bool is_convex(vector<Point>& points) {
  int n = points.size();
  int i = 0, j = 0, k = 0;
  double cp = 0;
  for (i = 0; i < n; i++) {
    j = (i + 1) % n;
    k = (i + 2) % n;
    
    double res = cross_product(points[i], points[j], points[k]);
    if (res != 0) {
      if (cp * res < 0) return false;
      else cp = res;
    }
  }
  return true;
}

// Driver code
int main() {
  double a[8];
  int p[8];
  for (int i = 0; i < 8; i++) {
    cin >> a[i];
    p[i] = i;
  }

  int ans = 0;
  double sq2 = sqrt(2);

  do {
    vector<Point> points(8);

    points[0] = {0, a[p[0]]};
    points[1] = {a[p[1]] / sq2, a[p[1]] / sq2};
    points[2] = {a[p[2]], 0};
    points[3] = {a[p[3]] / sq2, -a[p[3]] / sq2};
    points[4] = {0, -a[p[4]]};
    points[5] = {-a[p[5]] / sq2, -a[p[5]] / sq2};
    points[6] = {-a[p[6]], 0};
    points[7] = {-a[p[7]] / sq2, a[p[7]] / sq2};

    if (is_convex(points)) ans++;

  } while (next_permutation(p, p + 8));
  
  cout << ans << '\n';
}
