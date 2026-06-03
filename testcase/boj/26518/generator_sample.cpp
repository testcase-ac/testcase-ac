#include "testlib.h"
#include <vector>

using long_long = long long;

long_long pickValue(const std::vector<long_long>& values) {
    return values[rnd.next(static_cast<int>(values.size()))];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long_long LIMIT = 1000000000LL;
    long_long b = 1;
    long_long c = 1;
    long_long a1 = 1;
    long_long a2 = 1;

    int mode = rnd.next(6);
    if (mode == 0) {
        b = rnd.next(1LL, 8LL);
        c = rnd.next(1LL, 8LL);
        a1 = rnd.next(1LL, 12LL);
        a2 = rnd.next(1LL, 12LL);
    } else if (mode == 1) {
        b = 1;
        c = rnd.next(1LL, 20LL);
        a1 = rnd.next(1LL, 30LL);
        a2 = rnd.next(1LL, 30LL);
    } else if (mode == 2) {
        b = rnd.next(1LL, 20LL);
        c = 1;
        a1 = rnd.next(1LL, 30LL);
        a2 = rnd.next(1LL, 30LL);
    } else if (mode == 3) {
        std::vector<long_long> edgeValues = {1, 2, 3, 10, 1000, LIMIT - 1, LIMIT};
        b = pickValue(edgeValues);
        c = pickValue(edgeValues);
        a1 = pickValue(edgeValues);
        a2 = pickValue(edgeValues);
    } else if (mode == 4) {
        b = rnd.next(LIMIT - 1000000LL, LIMIT);
        c = rnd.next(1LL, 1000000LL);
        a1 = rnd.next(1LL, LIMIT);
        a2 = rnd.next(1LL, LIMIT);
    } else {
        b = rnd.next(1LL, LIMIT);
        c = rnd.next(1LL, LIMIT);
        a1 = rnd.next(1LL, LIMIT);
        a2 = rnd.next(1LL, LIMIT);
    }

    println(b, c, a1, a2);
    return 0;
}
