#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(1, 18);
    }

    int a;
    if (mode == 0) {
        a = rnd.next(1, 8);
    } else if (mode == 1) {
        a = rnd.next(250, 1000);
    } else {
        a = rnd.next(1, 1000);
    }

    vector<tuple<int, int, int>> crops;
    crops.reserve(n);

    for (int i = 0; i < n; ++i) {
        int x, y;
        if (mode == 0) {
            int d = rnd.next(0, 20);
            int sign = rnd.next(0, 1) ? 1 : -1;
            if (rnd.next(0, 1)) {
                x = sign * d;
                y = 0;
            } else {
                x = 0;
                y = sign * d;
            }
        } else if (mode == 1) {
            x = rnd.next(-3, 3);
            y = rnd.next(-3, 3);
        } else if (mode == 2) {
            int d = rnd.any(vector<int>{1, 2, 3, 5, 8, 13, 21});
            int sx = rnd.next(0, 1) ? 1 : -1;
            int sy = rnd.next(0, 1) ? 1 : -1;
            x = sx * d;
            y = sy * d;
        } else if (mode == 3) {
            x = rnd.next(-1000, 1000);
            y = rnd.next(-1000, 1000);
        } else if (mode == 4) {
            int ring = rnd.next(1, 30);
            int side = rnd.next(0, 7);
            if (side == 0) {
                x = ring;
                y = 0;
            } else if (side == 1) {
                x = -ring;
                y = 0;
            } else if (side == 2) {
                x = 0;
                y = ring;
            } else if (side == 3) {
                x = 0;
                y = -ring;
            } else {
                x = rnd.next(-ring, ring);
                y = rnd.next(-ring, ring);
            }
        } else {
            x = rnd.next(-60, 60);
            y = rnd.next(-60, 60);
        }

        int w;
        if (mode == 0) {
            w = rnd.next(120, 200);
        } else if (mode == 1) {
            w = rnd.next(1, 40);
        } else if (rnd.next(0, 4) == 0) {
            w = rnd.any(vector<int>{1, 2, 199, 200});
        } else {
            w = rnd.next(1, 200);
        }
        crops.emplace_back(x, y, w);
    }

    shuffle(crops.begin(), crops.end());

    println(n, a);
    for (auto [x, y, w] : crops) {
        println(x, y, w);
    }

    return 0;
}
