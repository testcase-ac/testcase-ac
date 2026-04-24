#include "testlib.h"
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const double PI = acos(-1);

    // Number of people
    int N = rnd.next(1, 8);
    // Guide speed
    double V = rnd.next(1.0, 100.0);

    // Output N and guide speed
    println(N);
    printf("%.2f\n", V);

    for (int i = 0; i < N; i++) {
        // Hyper: position distance from bus: cluster near or far
        double dist;
        if (rnd.next() < 0.3) dist = rnd.next(0.0, 100.0);
        else dist = rnd.next(100.0, 1000.0);
        double alphaPos = rnd.next(0.0, 2 * PI);
        double xi = dist * cos(alphaPos);
        double yi = dist * sin(alphaPos);

        // Person speed
        double vi = rnd.next(1.0, 100.0);

        // Movement direction ai in [1, 2π], cluster at cardinal angles or uniform
        double ai;
        if (rnd.next() < 0.5) {
            ai = rnd.next(1.0, 2 * PI);
        } else {
            vector<double> dirs = {PI/2, PI, 3*PI/2, 2*PI};
            double base = rnd.any(dirs);
            ai = base + rnd.next(-0.1, 0.1);
            if (ai < 1.0) ai = 1.0;
            if (ai > 2*PI) ai = 2*PI;
        }

        // Print one person
        printf("%.2f %.2f %.2f %.2f\n", xi, yi, vi, ai);
    }

    return 0;
}
