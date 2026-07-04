#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string fixed2(int cents) {
    bool neg = cents < 0;
    int v = abs(cents);

    ostringstream out;
    if (neg) out << '-';
    out << (v / 100) << '.' << setw(2) << setfill('0') << (v % 100);
    return out.str();
}

int randomCoord() {
    return rnd.next(-1000, 1000);
}

int edgeCoord() {
    static const vector<int> values = {
        -1000, -999, -1, 0, 1, 999, 1000,
    };
    return rnd.any(values);
}

int compactCoord() {
    return rnd.next(-200, 200);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 20);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int A;
        int B;
        int C;

        if (mode == 0) {
            A = compactCoord();
            B = compactCoord();
            C = compactCoord();
        } else if (mode == 1) {
            A = edgeCoord();
            B = edgeCoord();
            C = edgeCoord();
        } else if (mode == 2) {
            C = compactCoord();
            A = C + rnd.next(-5, 5);
            B = C + rnd.next(-5, 5);
            A = max(-1000, min(1000, A));
            B = max(-1000, min(1000, B));
        } else if (mode == 3) {
            A = compactCoord();
            B = -A + rnd.next(-50, 50);
            B = max(-1000, min(1000, B));
            C = rnd.next(-1000, 1000);
        } else if (mode == 4) {
            A = rnd.next(-1000, -900);
            B = rnd.next(900, 1000);
            C = rnd.next(-1000, 1000);
        } else {
            A = randomCoord();
            B = randomCoord();
            C = randomCoord();
        }

        println(1, fixed2(A), fixed2(B));
        println(fixed2(C));
    }

    return 0;
}
