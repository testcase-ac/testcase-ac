#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int signedValue(int magnitudeMode) {
    int value;
    if (magnitudeMode == 0) {
        value = rnd.next(0, 20);
    } else if (magnitudeMode == 1) {
        value = rnd.next(0, 10000);
    } else {
        static const vector<int> boundaryValues = {0, 1, 2, 9999, 10000};
        value = rnd.any(boundaryValues);
    }

    if (value != 0 && rnd.next(2) == 0) {
        value = -value;
    }
    return value;
}

vector<int> makeRound(int n, int mode) {
    vector<int> values(n);

    if (mode == 0) {
        for (int& value : values) {
            value = signedValue(0);
        }
    } else if (mode == 1) {
        for (int& value : values) {
            value = signedValue(1);
        }
    } else if (mode == 2) {
        for (int& value : values) {
            value = rnd.next(100) < 65 ? 0 : signedValue(2);
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            int magnitude = (i % 3 == 0 ? 10000 : rnd.next(0, 30));
            values[i] = rnd.next(2) == 0 ? -magnitude : magnitude;
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int sign = (i % 2 == 0 ? 1 : -1);
            if (rnd.next(100) < 25) {
                sign = -sign;
            }
            values[i] = sign * rnd.next(0, 10000);
        }
    }

    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(5);
    int n;
    if (sizeMode == 0) {
        n = rnd.next(1, 3);
    } else if (sizeMode == 1) {
        n = rnd.next(4, 8);
    } else if (sizeMode == 2) {
        n = rnd.next(9, 20);
    } else if (sizeMode == 3) {
        n = rnd.next(21, 60);
    } else {
        n = rnd.any(vector<int>{1, 2, 3, 100, 999, 10000});
    }

    int firstMode = rnd.next(5);
    int secondMode = rnd.next(5);

    println(n);
    println(makeRound(n, firstMode));
    println(makeRound(n, secondMode));

    return 0;
}
