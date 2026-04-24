#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Grid size (ensure at least 3x3 for variability)
    int R = rnd.next(3, 10);
    int C = rnd.next(3, 10);
    int maxS = min(R, C);

    // Two square sizes
    int s1 = rnd.next(1, maxS);
    int s2 = rnd.next(1, maxS);

    // First square position
    int r1 = rnd.next(1, R - s1 + 1);
    int c1 = rnd.next(1, C - s1 + 1);
    int r2, c2;

    // Helpers to check relations
    auto intersects = [&](int rr1, int cc1, int ss1, int rr2, int cc2, int ss2) {
        return !(rr2 > rr1 + ss1 - 1 || rr2 + ss2 - 1 < rr1 ||
                 cc2 > cc1 + ss1 - 1 || cc2 + ss2 - 1 < cc1);
    };
    auto contains = [&](int rr1, int cc1, int ss1, int rr2, int cc2, int ss2) {
        return rr2 >= rr1 && rr2 + ss2 - 1 <= rr1 + ss1 - 1 &&
               cc2 >= cc1 && cc2 + ss2 - 1 <= cc1 + ss1 - 1;
    };

    // Decide relation: nested (~30%), overlapping (~30%), disjoint (~40%)
    double p = rnd.next();
    if (p < 0.3) {
        // Nested: ensure one inside the other
        if (s1 < s2) swap(s1, s2), swap(r1, r1), swap(c1, c1);
        r1 = rnd.next(1, R - s1 + 1);
        c1 = rnd.next(1, C - s1 + 1);
        // Place square2 entirely inside square1
        r2 = rnd.next(r1, r1 + s1 - s2);
        c2 = rnd.next(c1, c1 + s1 - s2);
    } else if (p < 0.6) {
        // Overlapping but not nested (attempt)
        r2 = rnd.next(1, R - s2 + 1);
        c2 = rnd.next(1, C - s2 + 1);
        bool ok = false;
        for (int it = 0; it < 100 && !ok; it++) {
            bool inter = intersects(r1, c1, s1, r2, c2, s2);
            bool c12 = contains(r1, c1, s1, r2, c2, s2);
            bool c21 = contains(r2, c2, s2, r1, c1, s1);
            if (inter && !c12 && !c21) {
                ok = true;
                break;
            }
            r2 = rnd.next(1, R - s2 + 1);
            c2 = rnd.next(1, C - s2 + 1);
        }
        // fallback: any overlap/nested allowed
    } else {
        // Disjoint
        r2 = rnd.next(1, R - s2 + 1);
        c2 = rnd.next(1, C - s2 + 1);
        for (int it = 0; it < 100 && intersects(r1, c1, s1, r2, c2, s2); it++) {
            r2 = rnd.next(1, R - s2 + 1);
            c2 = rnd.next(1, C - s2 + 1);
        }
    }

    // If both are size 1, ensure they don't coincide (to have at least 2 'x')
    if (s1 == 1 && s2 == 1) {
        while (r2 == r1 && c2 == c1) {
            r2 = rnd.next(1, R - 1 + 1);
            c2 = rnd.next(1, C - 1 + 1);
        }
    }

    // Build the grid and mark both squares
    vector<string> grid(R, string(C, '.'));
    for (int i = r1 - 1; i < r1 - 1 + s1; i++)
        for (int j = c1 - 1; j < c1 - 1 + s1; j++)
            grid[i][j] = 'x';
    for (int i = r2 - 1; i < r2 - 1 + s2; i++)
        for (int j = c2 - 1; j < c2 - 1 + s2; j++)
            grid[i][j] = 'x';

    // Output
    println(R, C);
    for (auto &row : grid) println(row);

    return 0;
}
