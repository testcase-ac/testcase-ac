#include "testlib.h"

#include <algorithm>
#include <climits>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string toHex(long long value, bool useUppercaseDigits) {
    stringstream ss;
    ss << "0x" << hex;
    if (useUppercaseDigits) {
        ss << std::uppercase;
    }
    ss << value;
    return ss.str();
}

pair<long long, long long> makeSmallRange(const vector<long long>& fib) {
    int mode = rnd.next(4);
    if (mode == 0) {
        long long lo = rnd.next(0, 20);
        long long hi = rnd.next(lo + 1, min(80LL, lo + rnd.next(1, 25)));
        return {lo, hi};
    }
    if (mode == 1) {
        int idx = rnd.next(0, 16);
        long long lo = max(0LL, fib[idx] - rnd.next(0, 2));
        long long hi = fib[idx] + rnd.next(1, 4);
        return {lo, hi};
    }
    if (mode == 2) {
        int idx = rnd.next(3, 18);
        long long lo = fib[idx] + 1;
        long long hi = fib[idx + 1] - 1;
        if (lo >= hi) {
            hi = lo + 1;
        }
        return {lo, hi};
    }

    long long lo = rnd.next(0, 2);
    long long hi = rnd.next(1, 3);
    if (lo >= hi) {
        hi = lo + 1;
    }
    return {lo, hi};
}

pair<long long, long long> makeMediumRange(const vector<long long>& fib) {
    int idx = rnd.next(12, 45);
    int mode = rnd.next(3);
    if (mode == 0) {
        long long lo = fib[idx];
        long long hi = fib[idx + rnd.next(1, 4)];
        return {lo, hi};
    }
    if (mode == 1) {
        long long lo = fib[idx] + rnd.next(1, 30);
        long long hi = fib[idx + 1] - rnd.next(1, 10);
        if (lo >= hi) {
            hi = lo + 1;
        }
        return {lo, hi};
    }

    long long span = rnd.next(1, 1000);
    long long center = fib[idx] + rnd.next(-20, 20);
    long long lo = max(0LL, center - span / 2);
    long long hi = center + span;
    return {lo, hi};
}

pair<long long, long long> makeLargeRange(const vector<long long>& fib) {
    int mode = rnd.next(3);
    if (mode == 0) {
        int idx = rnd.next(70, 92);
        long long lo = max(0LL, fib[idx] - rnd.next(0, 1000000));
        long long hi = min(LLONG_MAX, fib[idx] + rnd.next(1, 1000000));
        return {lo, hi};
    }
    if (mode == 1) {
        long long lo = LLONG_MAX - rnd.next(1, 1000000);
        long long hi = LLONG_MAX;
        return {lo, hi};
    }

    int idx = rnd.next(65, 90);
    long long lo = fib[idx] + 1;
    long long hi = fib[idx + 1] - 1;
    if (lo >= hi) {
        hi = lo + 1;
    }
    return {lo, hi};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> fib = {0, 1};
    while (fib.back() <= LLONG_MAX - fib[fib.size() - 2]) {
        fib.push_back(fib.back() + fib[fib.size() - 2]);
    }

    int ranges = rnd.next(1, 12);
    vector<pair<long long, long long>> cases;
    cases.reserve(ranges);

    for (int i = 0; i < ranges; ++i) {
        int bucket = rnd.next(100);
        pair<long long, long long> range;
        if (bucket < 45) {
            range = makeSmallRange(fib);
        } else if (bucket < 80) {
            range = makeMediumRange(fib);
        } else {
            range = makeLargeRange(fib);
        }

        range.first = max(0LL, range.first);
        range.second = min(LLONG_MAX, range.second);
        if (range.first >= range.second) {
            range.first = max(0LL, range.second - 1);
        }
        cases.push_back(range);
    }

    for (auto [lo, hi] : cases) {
        bool upperLo = rnd.next(4) == 0;
        bool upperHi = rnd.next(4) == 0;
        println(toHex(lo, upperLo), toHex(hi, upperHi));
    }

    if (rnd.next(2) == 0) {
        long long stop = rnd.next(0, 20);
        println(toHex(stop, rnd.next(4) == 0), toHex(stop, rnd.next(4) == 0));
    }

    return 0;
}
