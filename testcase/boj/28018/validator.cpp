#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxTime = 1000000;

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int s = inf.readInt(1, maxTime, "S");
        inf.readSpace();
        int e = inf.readInt(s, maxTime, "E");
        inf.readEoln();
    }

    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    inf.readInts(q, 0, maxTime, "query_time");
    inf.readEoln();

    inf.readEof();
}
