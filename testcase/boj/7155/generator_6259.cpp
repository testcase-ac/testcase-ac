#include "testlib.h"
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const double PI = acos(-1.0);
    int T = rnd.next(5, 10);
    vector<int> special = {0, 90, 180, 270};
    for (int t = 0; t < T; t++) {
        int w, h, x, y, scale, rot;
        while (true) {
            // bias to smaller maps but allow up to 1000
            w = rnd.wnext(1000, -2) + 1;
            h = rnd.wnext(1000, -2) + 1;
            scale = rnd.next(1, 99);
            double w2 = w * scale / 100.0;
            double h2 = h * scale / 100.0;
            // choose rotation: sometimes special, else random
            if (rnd.next(0, 4) == 0) rot = rnd.any(special);
            else rot = rnd.next(0, 359);
            // choose offset
            x = rnd.next(0, w);
            y = rnd.next(0, h);
            double theta = rot * PI / 180.0;
            double c = cos(theta), s = sin(theta);
            bool ok = true;
            // corners of smaller after rotation
            vector<pair<double,double>> pts = {{0,0}, {w2,0}, {0,h2}, {w2,h2}};
            for (auto &p : pts) {
                double nx = x + p.first * c - p.second * s;
                double ny = y + p.first * s + p.second * c;
                if (nx < -1e-9 || nx > w + 1e-9 || ny < -1e-9 || ny > h + 1e-9) {
                    ok = false; break;
                }
            }
            if (ok) break;
        }
        println(w, h, x, y, scale, rot);
    }
    println(0, 0, 0, 0, 0, 0);
    return 0;
}
