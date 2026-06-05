#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MAX_TIME = 1000000000LL;

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<long long> endpoints;
    for (int i = 0; i < n; ++i) {
        long long start = inf.readLong(0LL, MAX_TIME, "start");
        inf.readSpace();
        long long end = inf.readLong(0LL, MAX_TIME, "end");
        inf.readEoln();

        ensuref(start < end, "shift %d has start >= end: %lld %lld", i + 1, start, end);
        ensuref(endpoints.insert(start).second, "duplicate endpoint at shift %d: %lld", i + 1, start);
        ensuref(endpoints.insert(end).second, "duplicate endpoint at shift %d: %lld", i + 1, end);
    }

    inf.readEof();
}
