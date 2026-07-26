#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 12);
    int r = rnd.next(1, 20);
    int m;

    if (mode == 0) {
        m = n;
    } else if (mode == 1) {
        r = rnd.next(1, 20);
        m = 2 * r * n;
    } else if (mode == 2) {
        r = rnd.next(500000000, 1000000000);
        m = rnd.next(n, 1000000000);
    } else if (mode == 3) {
        r = 1;
        m = rnd.next(n, 2 * n);
    } else {
        m = rnd.next(n, 2 * r * n);
    }

    set<int> chosen;
    while ((int)chosen.size() < n) chosen.insert(rnd.next(0, m - 1));
    vector<int> positions(chosen.begin(), chosen.end());
    shuffle(positions.begin(), positions.end());

    println(n);
    println(r, m);
    println(positions);
}
