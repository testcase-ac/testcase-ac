#include "testlib.h"

#include <vector>

using namespace std;

long long chooseFrom(const vector<long long>& values) {
    return values[rnd.next(0, static_cast<int>(values.size()) - 1)];
}

long long randomLimitValue() {
    const long long limit = 1000000000000000LL;
    int mode = rnd.next(0, 5);
    if (mode == 0) return rnd.next(1LL, 30LL);
    if (mode == 1) return rnd.next(999990LL, 1000010LL);
    if (mode == 2) return rnd.next(limit - 1000, limit);
    if (mode == 3) return chooseFrom({1LL, 2LL, 5LL, 10LL, 999999LL, 1000000LL, 1000001LL, limit});
    if (mode == 4) return rnd.next(1LL, 1000000000LL);
    return rnd.next(1LL, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxUnits = 200000000000000LL;

    long long units;
    int nMode = rnd.next(0, 5);
    if (nMode == 0) {
        units = rnd.next(1LL, 12LL);
    } else if (nMode == 1) {
        units = chooseFrom({1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 10LL, 20LL});
    } else if (nMode == 2) {
        units = rnd.next(100000LL, 100020LL);
    } else if (nMode == 3) {
        units = rnd.next(maxUnits - 100, maxUnits);
    } else if (nMode == 4) {
        units = chooseFrom({199999999999999LL, maxUnits});
    } else {
        units = rnd.next(1LL, maxUnits);
    }

    long long n = units * 5;
    long long k = randomLimitValue();
    long long l = randomLimitValue();

    if (rnd.next(0, 4) == 0) {
        vector<long long> nearModulo = {1LL, 999998LL, 999999LL, 1000000LL, 1000001LL, 1000002LL};
        if (rnd.next(0, 1) == 0) k = chooseFrom(nearModulo);
        if (rnd.next(0, 1) == 0) l = chooseFrom(nearModulo);
    }

    println(n, k, l);
    return 0;
}
