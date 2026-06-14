#include "testlib.h"
#include <array>
#include <vector>

using namespace std;

using Case = array<int, 5>;

int smallValue() {
    return rnd.next(0, 8);
}

int edgeValue() {
    const vector<int> values = {0, 1, 2, 3, 4, 99999999, 100000000};
    return rnd.any(values);
}

Case makeCase(int mode) {
    Case a = {smallValue(), smallValue(), smallValue(), smallValue(), smallValue()};

    if (mode == 0) {
        a = {0, 0, 0, rnd.next(0, 9), smallValue()};
    } else if (mode == 1) {
        a = {0, 0, 1, rnd.next(0, 9), smallValue()};
    } else if (mode == 2) {
        a = {0, 0, rnd.next(2, 8), smallValue(), smallValue()};
    } else if (mode == 3) {
        a = {rnd.next(1, 8), smallValue(), smallValue(), smallValue(), smallValue()};
    } else if (mode == 4) {
        a = {0, rnd.next(1, 8), smallValue(), smallValue(), smallValue()};
    } else if (mode == 5) {
        a = {edgeValue(), edgeValue(), edgeValue(), edgeValue(), edgeValue()};
    }

    if (rnd.next(0, 9) == 0) {
        int index = rnd.next(0, 4);
        a[index] = edgeValue();
    }

    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 30);
    println(t);
    for (int i = 0; i < t; ++i) {
        Case a = makeCase(rnd.next(0, 5));
        println(a[0], a[1], a[2], a[3], a[4]);
    }

    return 0;
}
