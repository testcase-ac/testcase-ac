#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // 2. Read Ian's scores
    vector<int> ian = inf.readInts(N, 0, 1000000000, "ian_score");
    inf.readEoln();

    // 3. Read Yehwan's scores
    vector<int> yehwan = inf.readInts(N, 0, 1000000000, "yehwan_score");
    inf.readEoln();

    // 4. No further global constraints in the statement (no duplicates, no sorted order, etc.)
    //    All constraints are per-value and already checked above.

    inf.readEof();
}
