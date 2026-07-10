#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

// Generates compact general-position point sets from the cubic moment curve.
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int mode = rnd.next(0, 3);
    const array<int, 4> minT = {-4, -8, -10, 0};
    const array<int, 4> maxT = {4, 8, 10, 10};
    const array<int, 4> maxN = {8, 10, 12, 10};
    const int n = rnd.next(4, maxN[mode]);

    vector<int> parameters;
    for (int t = minT[mode]; t <= maxT[mode]; ++t) {
        parameters.push_back(t);
    }
    shuffle(parameters.begin(), parameters.end());
    parameters.resize(n);

    vector<array<int, 3>> points;
    for (int t : parameters) {
        // Any four distinct (t, t^2, t^3) have a nonzero Vandermonde
        // determinant, so they cannot be coplanar.
        points.push_back({t, t * t, t * t * t});
    }

    array<int, 3> axis = {0, 1, 2};
    shuffle(axis.begin(), axis.end());
    array<int, 3> sign;
    for (int coordinate = 0; coordinate < 3; ++coordinate) {
        sign[coordinate] = rnd.next(0, 1) == 0 ? -1 : 1;
    }

    vector<array<int, 3>> transformed(n);
    for (int i = 0; i < n; ++i) {
        for (int coordinate = 0; coordinate < 3; ++coordinate) {
            transformed[i][coordinate] =
                sign[coordinate] * points[i][axis[coordinate]];
        }
    }

    for (int coordinate = 0; coordinate < 3; ++coordinate) {
        int minimum = transformed[0][coordinate];
        int maximum = transformed[0][coordinate];
        for (const auto& point : transformed) {
            minimum = min(minimum, point[coordinate]);
            maximum = max(maximum, point[coordinate]);
        }

        const int translation = rnd.next(
            max(-40, -1000 - minimum),
            min(40, 1000 - maximum));
        for (auto& point : transformed) {
            point[coordinate] += translation;
        }
    }

    shuffle(transformed.begin(), transformed.end());
    println(n);
    for (const auto& point : transformed) {
        println(point[0], point[1], point[2]);
    }

    return 0;
}
