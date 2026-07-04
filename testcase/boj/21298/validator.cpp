#include "testlib.h"

#include <array>
#include <algorithm>

using namespace std;

pair<int, int> lexicographicPair(int index) {
    for (int a = 0; a < 11; ++a) {
        for (int b = a + 1; b < 11; ++b) {
            if (index == 0) {
                return {a, b};
            }
            --index;
        }
    }
    ensuref(false, "invalid operation pair index");
    return {0, 1};
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    array<int, 11> dim;
    long long total = 1;
    for (int i = 0; i < 11; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        dim[i] = inf.readInt(1, 111111, format("dim_%d", i + 1));
        total *= dim[i];
        ensuref(total <= 111111, "dimension product exceeds 111111");
    }
    inf.readEoln();

    long long rows = total / dim[10];
    for (long long row = 0; row < rows; ++row) {
        for (int w = 0; w < dim[10]; ++w) {
            if (w > 0) {
                inf.readSpace();
            }
            inf.readLong(1LL, 11111111111LL, "a");
        }
        inf.readEoln();
    }

    int rho = inf.readInt(1, 111111, "rho");
    inf.readEoln();

    int boundedOperationCount = 0;
    for (int i = 1; i <= rho; ++i) {
        setTestCase(i);

        int op = inf.readInt(1, 121, "op");
        if (op <= 66) {
            ++boundedOperationCount;
            ensuref(boundedOperationCount <= 1111,
                    "more than 1111 operations with 1 <= op <= 66");

            array<int, 11> lo;
            array<int, 11> hi;
            for (int j = 0; j < 11; ++j) {
                inf.readSpace();
                lo[j] = inf.readInt(1, dim[j], format("lo_%d", j + 1));
            }
            for (int j = 0; j < 11; ++j) {
                inf.readSpace();
                hi[j] = inf.readInt(1, dim[j], format("hi_%d", j + 1));
                ensuref(lo[j] <= hi[j],
                        "lower coordinate exceeds upper coordinate at dimension %d", j + 1);
            }

            if (op >= 12) {
                auto [first, second] = lexicographicPair(op - 12);

                ensuref(lo[first] < hi[first] && lo[second] < hi[second],
                        "operation %d requires positive span in dimensions %d and %d",
                        op, first + 1, second + 1);
                int spanA = hi[first] - lo[first];
                int spanB = hi[second] - lo[second];
                ensuref(min(spanA, spanB) % 2 == 1,
                        "operation %d requires odd minimum span", op);
            }
        } else {
            auto [first, second] = lexicographicPair(op - 67);
            swap(dim[first], dim[second]);
        }
        inf.readEoln();
    }

    inf.readEof();
}
