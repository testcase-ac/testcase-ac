#include "testlib.h"

#include <cmath>
#include <cstdio>

using namespace std;

namespace {

constexpr int TEST_CASES = 100;
constexpr int SAMPLE_SIZE = 5000;
constexpr double PI = 3.14159265358979323846;

int roundedUniform() {
    return rnd.next(0, 10000);
}

double standardNormal() {
    double u1 = rnd.next();
    double u2 = rnd.next();
    if (u1 < 1e-12) u1 = 1e-12;
    return sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
}

int roundedTruncatedNormal() {
    constexpr double mean = 0.5;
    constexpr double stddev = sqrt(0.1);

    while (true) {
        double x = mean + stddev * standardNormal();
        if (0.0 <= x && x <= 1.0) {
            int scaled = static_cast<int>(floor(x * 10000.0 + 0.5));
            if (0 <= scaled && scaled <= 10000) return scaled;
        }
    }
}

void printScaled(int scaled) {
    printf("%d.%04d\n", scaled / 10000, scaled % 10000);
}

} // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    for (int tc = 0; tc < TEST_CASES; ++tc) {
        int mode = rnd.next(0, 3);

        for (int i = 0; i < SAMPLE_SIZE; ++i) {
            int scaled;
            if (mode == 0) {
                scaled = roundedUniform();
            } else if (mode == 1) {
                scaled = roundedTruncatedNormal();
            } else if (mode == 2) {
                scaled = (i % 2 == 0) ? roundedUniform() : roundedTruncatedNormal();
            } else {
                int bucket = rnd.next(0, 9);
                int lo = bucket * 1000;
                int hi = (bucket == 9) ? 10000 : lo + 999;
                scaled = rnd.next(lo, hi);
            }
            printScaled(scaled);
        }
    }

    return 0;
}
