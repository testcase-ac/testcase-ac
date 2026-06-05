#include "testlib.h"

using namespace std;

long long bill(long long usage) {
    long long total = 0;

    long long take = min(usage, 100LL);
    total += take * 2;
    usage -= take;

    take = min(usage, 9900LL);
    total += take * 3;
    usage -= take;

    take = min(usage, 990000LL);
    total += take * 5;
    usage -= take;

    total += usage * 7;
    return total;
}

long long usageForBill(long long target) {
    long long lo = 1;
    long long hi = 200000000LL;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (bill(mid) >= target) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return bill(lo) == target ? lo : -1;
}

bool hasUniqueSplit(long long totalUsage, long long diff) {
    long long lo = 1;
    long long hi = totalUsage / 2;
    if (hi < lo) {
        return false;
    }

    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        long long current = bill(totalUsage - mid) - bill(mid);
        if (current <= diff) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    return bill(totalUsage - lo) - bill(lo) == diff;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        long long a = inf.readLong(0LL, 1000000000LL, "A");
        inf.readSpace();
        long long b = inf.readLong(0LL, 1000000000LL, "B");
        inf.readEoln();

        if (a == 0 && b == 0) {
            break;
        }

        setTestCase(cases + 1);
        ensuref(1 <= a && a <= 1000000000LL, "A out of range: %lld", a);
        ensuref(1 <= b && b <= 1000000000LL, "B out of range: %lld", b);

        // CHECK: the statement has no test case count bound; use the local default cap.
        ++cases;
        ensuref(cases <= 100000, "too many test cases: %d", cases);

        long long totalUsage = usageForBill(a);
        ensuref(totalUsage != -1, "A is not an achievable combined bill: %lld", a);
        ensuref(hasUniqueSplit(totalUsage, b),
                "no unique valid consumption split for A=%lld B=%lld", a, b);
    }

    inf.readEof();
}
