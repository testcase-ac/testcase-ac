#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    int d;
    vector<int> xs;

    if (mode == 0) {
        n = rnd.next(1, 12);
        d = rnd.next(1, 25);
        int sign = rnd.next(0, 1) ? 1 : -1;
        for (int i = 0; i < n; ++i) xs.push_back(sign * rnd.next(0, 30));
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        d = rnd.next(1, 80);
        for (int i = 0; i < n; ++i) xs.push_back(rnd.next(-40, 40));
    } else if (mode == 2) {
        n = rnd.next(3, 25);
        d = rnd.next(1, 100);
        vector<int> pool = {0, rnd.next(-20, -1), rnd.next(1, 20)};
        for (int i = 0; i < n; ++i) xs.push_back(rnd.any(pool));
    } else if (mode == 3) {
        n = rnd.next(4, 30);
        d = rnd.next(1, 1000);
        int center = rnd.next(-200, 200);
        int radius = rnd.next(0, 12);
        for (int i = 0; i < n; ++i) xs.push_back(center + rnd.next(-radius, radius));
    } else if (mode == 4) {
        n = rnd.next(2, 16);
        d = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            int base = rnd.next(0, 1) ? 1000000000 : -1000000000;
            xs.push_back(base + (base > 0 ? -rnd.next(0, 1000) : rnd.next(0, 1000)));
        }
    } else if (mode == 5) {
        n = 2 * rnd.next(1, 10) + rnd.next(0, 1);
        d = rnd.next(1, 200);
        if (n % 2 == 1) xs.push_back(0);
        while ((int)xs.size() < n) {
            int v = rnd.next(1, 70);
            xs.push_back(-v);
            xs.push_back(v);
        }
    } else {
        n = rnd.next(1, 40);
        d = rnd.next(1, 1000000000);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 4);
            if (bucket == 0) xs.push_back(0);
            else if (bucket == 1) xs.push_back(rnd.next(-5, 5));
            else if (bucket == 2) xs.push_back(rnd.next(-1000, 1000));
            else if (bucket == 3) xs.push_back(rnd.next(-1000000, 1000000));
            else xs.push_back(rnd.next(-1000000000, 1000000000));
        }
    }

    shuffle(xs.begin(), xs.end());

    println(n, d);
    println(xs);

    return 0;
}
