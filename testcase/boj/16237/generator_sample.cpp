#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int smallCount() {
    return rnd.next(0, 25);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> x(5, 0);
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        int weight = rnd.next(0, 4);
        x[weight] = rnd.next(0, 1000);
    } else if (mode == 1) {
        x[0] = rnd.next(0, 80);
        x[3] = rnd.next(0, 80);
        x[1] = rnd.next(0, 10);
        x[2] = rnd.next(0, 10);
        x[4] = rnd.next(0, 10);
    } else if (mode == 2) {
        x[1] = rnd.next(0, 80);
        x[2] = rnd.next(0, 80);
        x[0] = rnd.next(0, 12);
        x[3] = rnd.next(0, 12);
        x[4] = rnd.next(0, 12);
    } else if (mode == 3) {
        x[0] = rnd.next(0, 120);
        x[1] = rnd.next(0, 120);
        x[2] = rnd.next(0, 120);
    } else if (mode == 4) {
        for (int i = 0; i < 5; ++i) x[i] = smallCount();
    } else if (mode == 5) {
        for (int i = 0; i < 5; ++i) x[i] = rnd.next(0, 1000);
    } else if (mode == 6) {
        for (int i = 0; i < 5; ++i) x[i] = rnd.next(995, 1000);
        int keep = rnd.next(1, 5);
        shuffle(x.begin(), x.end());
        for (int i = keep; i < 5; ++i) x[i] = rnd.next(0, 3);
    } else {
        x[0] = rnd.next(0, 40);
        x[1] = rnd.next(0, 40);
        x[2] = rnd.next(0, 40);
        x[3] = rnd.next(0, 40);
        x[4] = rnd.next(0, 40);
        if (rnd.next(0, 1)) x[rnd.next(0, 4)] = 1000;
    }

    println(x[0], x[1], x[2], x[3], x[4]);
    return 0;
}
