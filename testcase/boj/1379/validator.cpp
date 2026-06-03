#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 0; i < n; ++i) {
        int id = inf.readInt(1, n, "lecture_number");
        inf.readSpace();
        long long start = inf.readLong(0LL, 1000000000LL, "start_time");
        inf.readSpace();
        long long end = inf.readLong(0LL, 1000000000LL, "end_time");
        inf.readEoln();

        ensuref(!seen[id], "duplicate lecture number %d at row %d", id, i + 1);
        seen[id] = true;
        ensuref(start < end, "lecture %d has start time %lld >= end time %lld", id, start, end);
    }

    inf.readEof();
}
