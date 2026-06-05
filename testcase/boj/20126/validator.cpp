#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000LL, "m");
    inf.readSpace();
    long long s = inf.readLong(m, 1000000000LL, "s");
    inf.readEoln();

    vector<pair<long long, long long>> exams;
    exams.reserve(n);

    for (int i = 0; i < n; ++i) {
        long long x = inf.readLong(0LL, s - 1, "x_i");
        inf.readSpace();
        long long y = inf.readLong(1LL, s - x, "y_i");
        inf.readEoln();

        exams.emplace_back(x, x + y);
    }

    sort(exams.begin(), exams.end());
    for (int i = 1; i < n; ++i) {
        ensuref(exams[i - 1].second <= exams[i].first,
                "exams overlap after sorting: previous [%lld, %lld), current [%lld, %lld)",
                exams[i - 1].first, exams[i - 1].second,
                exams[i].first, exams[i].second);
    }

    inf.readEof();
}
