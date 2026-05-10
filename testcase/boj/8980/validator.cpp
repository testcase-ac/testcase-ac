#include "testlib.h"
#include <vector>
#include <set>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, C
    int N = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int C = inf.readInt(1, 10000, "C");
    inf.readEoln();

    // 2. Read M
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // 3. Read M lines of (from, to, num)
    //    - 1 <= from < to <= N
    //    - 1 <= num <= 10000
    //    - No further constraints (multiple same (from,to) allowed)
    for (int i = 0; i < M; ++i) {
        int from = inf.readInt(1, N-1, "from");
        inf.readSpace();
        int to = inf.readInt(from+1, N, "to");
        inf.readSpace();
        int num = inf.readInt(1, 10000, "num");
        inf.readEoln();
    }

    inf.readEof();
}
