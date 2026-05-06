#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read 6 integers a_1..a_6, clockwise, each in [2,6]
    vector<int> a(6);
    for (int i = 0; i < 6; ++i) {
        a[i] = inf.readInt(2, 6, ("a_" + to_string(i+1)).c_str());
        if (i < 5) inf.readSpace();
    }
    inf.readEoln();

    // The problem says: "주어진 입력은 올바른 육각형을 이룬다."
    // So we do not need to check for polygon validity.

    // However, let's check for non-degeneracy (area > 0)
    // The hexagon described is a "regular" hexagon with possibly different side lengths,
    // but with all internal angles 120 degrees.
    // The area can be computed by the shoelace formula if we construct the coordinates.

    // Let's construct the coordinates of the vertices.
    // Start at (0,0), and for each side, move by a_i in the direction of 0, 60, 120, 180, 240, 300 degrees.

    vector<double> x(7), y(7);
    double angle = 0.0;
    x[0] = 0.0;
    y[0] = 0.0;
    for (int i = 0; i < 6; ++i) {
        angle = i * M_PI / 3.0; // 0, pi/3, 2pi/3, pi, 4pi/3, 5pi/3
        x[i+1] = x[i] + a[i] * cos(angle);
        y[i+1] = y[i] + a[i] * sin(angle);
    }
    // Check that the polygon is closed (last point == first point)
    double dx = x[6] - x[0], dy = y[6] - y[0];
    ensuref(fabs(dx) < 1e-6 && fabs(dy) < 1e-6,
        "Hexagon is not closed: last vertex differs from first by (%lf, %lf)", dx, dy);

    // Compute area by shoelace formula
    double area = 0.0;
    for (int i = 0; i < 6; ++i) {
        area += x[i] * y[i+1] - x[i+1] * y[i];
    }
    area = fabs(area) / 2.0;
    ensuref(area > 1e-6, "Degenerate hexagon: area is zero");

    inf.readEof();
}
