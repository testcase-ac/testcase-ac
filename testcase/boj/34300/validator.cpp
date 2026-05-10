#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int C = inf.readInt(1, 500, "C");
    inf.readEoln();

    long long totalShirts = 0;
    for (int i = 0; i < C; ++i) {
        int s = inf.readInt(1, 500, "S_i");
        inf.readEoln();
        totalShirts += s;
    }

    // Optional: basic sanity check that totalShirts is within expected bounds
    ensuref(totalShirts >= 1 && totalShirts <= 1LL * 500 * 500,
            "Total number of shirts out of expected range");

    inf.readEof();
}
