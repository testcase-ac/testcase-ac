#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Predefined small Pythagorean triples (a, b, r) with a^2 + b^2 = r^2
    vector<array<int,3>> triples = {
        {3, 4, 5},
        {5, 12, 13},
        {8, 15, 17},
        {7, 24, 25},
        {20, 21, 29}
    };

    int k = rnd.next(3, 7);
    println(k);

    bool usedValid = false, usedInvalid = false;
    for (int i = 1; i <= k; i++) {
        bool makeValid;
        if (i == k) {
            if (!usedValid) makeValid = true;
            else if (!usedInvalid) makeValid = false;
            else makeValid = rnd.next(0,1);
        } else {
            makeValid = rnd.next(0,1);
        }

        vector<pair<int,int>> pts;
        if (makeValid) {
            usedValid = true;
            // Generate a valid circle (special case of ellipse) with integer lattice points
            auto t = rnd.any(triples);
            int a = t[0], b = t[1]; // radius r = t[2]
            // Generate the 8 lattice points on the circle centered at (0,0)
            for (int s1 : {-1, 1}) {
                for (int s2 : {-1, 1}) {
                    pts.emplace_back(s1 * a, s2 * b);
                    pts.emplace_back(s1 * b, s2 * a);
                }
            }
            // Random center shift
            int cx = rnd.next(-20, 20);
            int cy = rnd.next(-20, 20);
            shuffle(pts.begin(), pts.end());
            pts.resize(5);
            for (auto &p : pts) {
                p.first += cx;
                p.second += cy;
            }
        } else {
            usedInvalid = true;
            // Generate 5 collinear points (no valid ellipse)
            bool vertical = rnd.next(0,1) == 0;
            if (vertical) {
                int x0 = rnd.next(-20, 20);
                vector<int> ys;
                while ((int)ys.size() < 5) {
                    int y = rnd.next(-20, 20);
                    if (find(ys.begin(), ys.end(), y) == ys.end())
                        ys.push_back(y);
                }
                for (int y : ys) pts.emplace_back(x0, y);
            } else {
                int m = rnd.next(-2, 2); // slope m
                int c_y = rnd.next(-5, 5);
                vector<int> xs;
                while ((int)xs.size() < 5) {
                    int x = rnd.next(-20, 20);
                    if (find(xs.begin(), xs.end(), x) == xs.end())
                        xs.push_back(x);
                }
                for (int x : xs) {
                    int y = m * x + c_y;
                    pts.emplace_back(x, y);
                }
            }
            shuffle(pts.begin(), pts.end());
        }
        // Prepare line of 10 integers
        vector<int> line;
        for (auto &p : pts) {
            line.push_back(p.first);
            line.push_back(p.second);
        }
        println(line);
    }

    return 0;
}
