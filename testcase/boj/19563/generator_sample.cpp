#include "testlib.h"

#include <algorithm>
#include <cstdlib>

using namespace std;

const long long COORD_LIMIT = 1000000000LL;
const long long JUMP_LIMIT = 2000000000LL;

long long randomCoord(long long limit) {
    return rnd.next(-limit, limit);
}

long long signedPart(long long total) {
    long long x = rnd.next(0LL, total);
    if (rnd.next(0, 1) == 1) {
        x = -x;
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long a = 0;
    long long b = 0;
    long long c = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = randomCoord(20);
        b = randomCoord(20);
        c = rnd.next(0LL, 50LL);
    } else if (mode == 1) {
        c = rnd.next(0LL, 80LL);
        long long dist = rnd.next(0LL, c / 2) * 2 + (c % 2);
        long long xAbs = rnd.next(0LL, dist);
        long long yAbs = dist - xAbs;
        a = signedPart(xAbs);
        b = signedPart(yAbs);
    } else if (mode == 2) {
        c = rnd.next(1LL, 80LL);
        long long dist = rnd.next(0LL, (c - 1) / 2) * 2 + ((c + 1) % 2);
        long long xAbs = rnd.next(0LL, dist);
        long long yAbs = dist - xAbs;
        a = signedPart(xAbs);
        b = signedPart(yAbs);
    } else if (mode == 3) {
        c = rnd.next(0LL, 80LL);
        long long dist = rnd.next(c + 1, min(JUMP_LIMIT, c + 80));
        long long xAbs = rnd.next(0LL, min(COORD_LIMIT, dist));
        long long yAbs = dist - xAbs;
        if (yAbs > COORD_LIMIT) {
            yAbs = COORD_LIMIT;
            xAbs = dist - yAbs;
        }
        a = signedPart(xAbs);
        b = signedPart(yAbs);
    } else if (mode == 4) {
        long long edge = rnd.next(COORD_LIMIT - 100, COORD_LIMIT);
        a = rnd.next(0, 1) == 0 ? edge : -edge;
        b = randomCoord(100);
        long long dist = llabs(a) + llabs(b);
        c = rnd.next(max(0LL, dist - 5), min(JUMP_LIMIT, dist + 5));
    } else {
        a = randomCoord(COORD_LIMIT);
        b = randomCoord(COORD_LIMIT);
        long long dist = llabs(a) + llabs(b);
        c = rnd.next(max(0LL, dist - 1000), min(JUMP_LIMIT, dist + 1000));
    }

    println(a, b, c);
    return 0;
}
