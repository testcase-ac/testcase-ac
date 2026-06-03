#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 99999, "N");
    ensuref(n % 2 == 1, "N must be odd, found %d", n);
    inf.readEoln();

    vector<int> juwon = inf.readInts(n, 0, 100000, "juwon_card");
    inf.readEoln();

    vector<int> boss = inf.readInts(n, 0, 100000, "boss_card");
    inf.readEoln();

    inf.readEof();
}
