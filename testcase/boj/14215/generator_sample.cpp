#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> sticks(3);
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        // Already a triangle, often near equal lengths.
        int base = rnd.next(1, 100);
        for (int& x : sticks) x = max(1, min(100, base + rnd.next(-5, 5)));
    } else if (mode == 1) {
        // Exactly degenerate before shortening: largest equals the sum of others.
        int a = rnd.next(1, 50);
        int b = rnd.next(1, 50);
        sticks = {a, b, min(100, a + b)};
    } else if (mode == 2) {
        // One stick is much longer than the other two.
        int a = rnd.next(1, 10);
        int b = rnd.next(1, 10);
        int c = rnd.next(50, 100);
        sticks = {a, b, c};
    } else if (mode == 3) {
        // Boundary-heavy cases near the validator limits.
        vector<int> choices = {1, 2, 3, 98, 99, 100};
        for (int& x : sticks) x = rnd.any(choices);
    } else if (mode == 4) {
        // Small triples are easy to inspect and often expose off-by-one logic.
        for (int& x : sticks) x = rnd.next(1, 10);
    } else {
        for (int& x : sticks) x = rnd.next(1, 100);
    }

    shuffle(sticks.begin(), sticks.end());
    println(sticks);
    return 0;
}
