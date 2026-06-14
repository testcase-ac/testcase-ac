#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<int> times;
    times.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int t = inf.readInt(0, 2000000, "time");
        if (!times.empty()) {
            ensuref(times.back() < t,
                    "touch times must be strictly increasing: t[%d]=%d, t[%d]=%d",
                    i, times.back(), i + 1, t);
        }
        times.push_back(t);
    }
    inf.readEoln();
    inf.readEof();
}
