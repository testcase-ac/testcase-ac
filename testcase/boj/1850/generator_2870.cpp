#include "testlib.h"
#include <numeric>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    uint64_t a, b;
    while (true) {
        int t = rnd.next(0, 3);
        if (t == 0) {
            // small random
            a = rnd.next(1, 100);
            b = rnd.next(1, 100);
        } else if (t == 1) {
            // equal numbers
            uint64_t x = rnd.next(1, 1000);
            a = x; b = x;
        } else if (t == 2) {
            // one is multiple of the other
            uint64_t g = rnd.next(1, 1000);
            uint64_t k = rnd.next(1, 1000);
            uint64_t m = rnd.next(1, 1000);
            a = g * k;
            b = g * m;
        } else {
            // large 60-bit randoms
            uint64_t hi1 = rnd.next(0, (1<<30) - 1);
            uint64_t lo1 = rnd.next(0, (1<<30) - 1);
            uint64_t hi2 = rnd.next(0, (1<<30) - 1);
            uint64_t lo2 = rnd.next(0, (1<<30) - 1);
            a = (hi1 << 30) | lo1;
            b = (hi2 << 30) | lo2;
            if (a == 0) a = 1;
            if (b == 0) b = 1;
        }
        uint64_t g = std::gcd(a, b);
        if (g <= 10000000) break;  // ensure output length <= 10^7
    }

    println(a, b);
    return 0;
}
