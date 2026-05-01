#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Bias for small, medium, large sizes
    vector<int> biases = {-1, 0, 1};
    int sizeBias = rnd.any(biases);
    // Possible polygon sizes
    vector<int> ns = {3, 4, 5, 6, 7, 8, 10, 12};
    int idx = rnd.wnext((int)ns.size(), sizeBias);
    int n = ns[idx];

    // Random center
    int Cx = rnd.next(-100, 100);
    int Cy = rnd.next(-100, 100);

    // Randomly choose circle or ellipse
    bool ellipse = rnd.next(0, 1) == 1;
    int Rx = rnd.next(20, 100);
    int Ry = ellipse ? rnd.next(20, 100) : Rx;

    const double PI = acos(-1.0);
    vector<pair<int,int>> pts;
    pts.reserve(n);
    for (int i = 0; i < n; i++) {
        double angle = -2.0 * PI * i / n;  // clockwise
        double x = Cx + Rx * cos(angle);
        double y = Cy + Ry * sin(angle);
        int xi = int(floor(x + 0.5));
        int yi = int(floor(y + 0.5));
        pts.emplace_back(xi, yi);
    }

    // Output the convex polygon in clockwise order
    println(n);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
