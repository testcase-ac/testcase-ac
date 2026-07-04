#include "testlib.h"

#include <vector>

long long sequenceSum(long long first, int length) {
    return first * length + 1LL * length * (length - 1) / 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n = 1;
    int l = 2;

    if (mode == 0) {
        n = rnd.next(1LL, 30LL);
        l = rnd.next(2, 10);
    } else if (mode == 1) {
        l = rnd.next(2, 100);
        int length = rnd.next(l, 100);
        long long maxFirst = (1000000000LL - 1LL * length * (length - 1) / 2) / length;
        long long first = rnd.next(0LL, maxFirst);
        n = sequenceSum(first, length);
    } else if (mode == 2) {
        int length = rnd.next(2, 100);
        long long maxFirst = (1000000000LL - 1LL * length * (length - 1) / 2) / length;
        long long first = rnd.next(0LL, maxFirst);
        n = sequenceSum(first, length);
        l = rnd.next(2, length);
    } else if (mode == 3) {
        n = rnd.next(900000000LL, 1000000000LL);
        l = rnd.next(2, 100);
    } else if (mode == 4) {
        l = rnd.any(std::vector<int>{2, 3, 4, 5, 50, 99, 100});
        n = rnd.any(std::vector<long long>{1LL, 2LL, 3LL, 45LL, 1000000000LL});
    } else {
        l = rnd.next(90, 100);
        n = rnd.next(1LL, 1000000LL);
    }

    println(n, l);
    return 0;
}
