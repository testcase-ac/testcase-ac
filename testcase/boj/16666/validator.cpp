#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 100000000, "k");
        inf.readEoln();

        vector<int> a = inf.readInts(7, 0, 1, "a_i");
        inf.readEoln();

        int classDays = 0;
        for (int value : a) {
            classDays += value;
        }
        ensuref(classDays >= 1, "test case %d has no class days", tc);
    }

    inf.readEof();
}
