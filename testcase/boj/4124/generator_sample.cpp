#include "testlib.h"
#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>
using namespace std;

using int64 = long long;

const int64 kIntMin = -2147483648LL;
const int64 kIntMax = 2147483647LL;

bool fitsInt(int64 x) {
    return kIntMin <= x && x <= kIntMax;
}

pair<int64, int64> makePossibleCase() {
    int degree = rnd.next(0, 5);
    vector<int64> coeffs(degree + 1);
    int64 sum = 0;

    for (int i = 0; i <= degree; ++i) {
        coeffs[i] = rnd.next(0, 8);
        sum += coeffs[i];
    }
    if (sum == 0 && rnd.next(0, 4) != 0) {
        int pos = rnd.next(0, degree);
        coeffs[pos] = rnd.next(1, 8);
        sum += coeffs[pos];
    }

    int64 f1 = sum;
    int64 ff1 = 0;
    for (int i = 0; i <= degree; ++i) {
        if (ff1 > (kIntMax - coeffs[i]) / max(1LL, f1)) {
            return make_pair(0, 0);
        }
        ff1 = ff1 * f1 + coeffs[i];
    }

    if (!fitsInt(ff1)) return make_pair(0, 0);
    return make_pair(f1, ff1);
}

pair<int64, int64> makeCase() {
    int mode = rnd.next(0, 7);

    if (mode <= 2) return makePossibleCase();
    if (mode == 3) return make_pair(1, rnd.next(0, 3) == 0 ? 1 : rnd.next(0, 100));
    if (mode == 4) return make_pair(0, rnd.next(-5, 5));
    if (mode == 5) return make_pair(rnd.next(-20, -1), rnd.next(-30, 30));
    if (mode == 6) {
        int64 f1 = rnd.next(2, 30);
        int64 ff1 = rnd.next(0, 1000);
        return make_pair(f1, ff1);
    }

    vector<int64> edgeValues = {kIntMin, -1, 0, 1, kIntMax};
    return make_pair(rnd.any(edgeValues), rnd.any(edgeValues));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 30);
    println(n);
    for (int i = 0; i < n; ++i) {
        auto [f1, ff1] = makeCase();
        println(f1, ff1);
    }

    return 0;
}
