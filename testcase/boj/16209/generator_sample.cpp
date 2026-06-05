#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 40);
    if (mode == 5) n = rnd.next(35, 120);

    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        int hi = rnd.next(1, 1000000);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, hi));
    } else if (mode == 1) {
        int lo = rnd.next(-1000000, -1);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, 0));
    } else if (mode == 2) {
        int span = rnd.next(1, 50);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(-span, span));
    } else if (mode == 3) {
        vector<int> pool = {-1000000, -rnd.next(1, 1000), 0, rnd.next(1, 1000), 1000000};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 4) {
        int x = rnd.next(-1000000, 1000000);
        int y = rnd.next(-1000000, 1000000);
        int z = rnd.next(-1000000, 1000000);
        vector<int> pool = {x, y, z, 0};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else {
        int negatives = rnd.next(1, n - 1);
        for (int i = 0; i < negatives; ++i) a.push_back(-rnd.next(1, 1000000));
        while ((int)a.size() < n) a.push_back(rnd.next(0, 1000000));
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
