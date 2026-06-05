#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int a = 2;
    int b = 1;

    if (mode == 0) {
        b = rnd.next(1, 12);
        int k = rnd.next(1, b);
        a = b + k;
    } else if (mode == 1) {
        b = rnd.next(2, 20);
        a = b;
    } else if (mode == 2) {
        b = rnd.next(2, 20);
        a = rnd.next(2, b);
    } else if (mode == 3) {
        b = rnd.next(1, 20);
        a = rnd.next(2 * b + 1, min(100, 2 * b + 20));
    } else if (mode == 4) {
        vector<pair<int, int>> edges = {{2, 1}, {3, 1}, {4, 2}, {8, 3}, {100, 100}, {100, 50}};
        auto chosen = rnd.any(edges);
        a = chosen.first;
        b = chosen.second;
    } else {
        a = rnd.next(2, 100);
        b = rnd.next(1, 100);
    }

    println(a, b);
    return 0;
}
