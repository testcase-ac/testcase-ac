#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int n = rnd.next(1, 10);           // number of points
    double axisProb = rnd.next();      // probability a point lies on an axis
    int coordMax = rnd.next(5, 20);    // maximum absolute coordinate
    int weightScale = rnd.next(1, 10); // scale for quadrant weighting

    vector<pair<int,int>> pts;
    pts.reserve(n);

    for (int i = 0; i < n; i++) {
        if (rnd.next() < axisProb) {
            // Generate an axis point (could be origin, x-axis, or y-axis)
            int t = rnd.next(0, 2);
            int x, y;
            if (t == 0) {
                x = 0; y = 0;
            } else if (t == 1) {
                x = 0;
                y = rnd.next(1, coordMax) * (rnd.next(0, 1) ? 1 : -1);
            } else {
                y = 0;
                x = rnd.next(1, coordMax) * (rnd.next(0, 1) ? 1 : -1);
            }
            pts.emplace_back(x, y);
        } else {
            // Generate a quadrant point
            int w[4], sum = 0;
            for (int k = 0; k < 4; k++) {
                w[k] = rnd.next(1, weightScale);
                sum += w[k];
            }
            int r = rnd.next(1, sum), acc = 0, q = 0;
            for (int k = 0; k < 4; k++) {
                acc += w[k];
                if (r <= acc) {
                    q = k;
                    break;
                }
            }
            int ax = rnd.next(1, coordMax);
            int ay = rnd.next(1, coordMax);
            int x, y;
            if (q == 0)      { x =  ax; y =  ay; }
            else if (q == 1) { x = -ax; y =  ay; }
            else if (q == 2) { x = -ax; y = -ay; }
            else             { x =  ax; y = -ay; }
            pts.emplace_back(x, y);
        }
    }

    // Output
    println(n);
    for (auto &p : pts)
        println(p.first, p.second);

    return 0;
}
