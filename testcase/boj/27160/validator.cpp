#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 100000;

    int N = inf.readInt(1, MAXN, "N");
    inf.readEoln();

    long long sum[4] = {0, 0, 0, 0}; // 0: STRAWBERRY, 1: BANANA, 2: LIME, 3: PLUM

    for (int i = 0; i < N; ++i) {
        string S = inf.readToken("[A-Z]+", "S");
        inf.readSpace();
        int X = inf.readInt(1, 5, "X");
        inf.readEoln();

        int id = -1;
        if (S == "STRAWBERRY") id = 0;
        else if (S == "BANANA") id = 1;
        else if (S == "LIME") id = 2;
        else if (S == "PLUM") id = 3;

        ensuref(id != -1,
                "Invalid fruit name at line %d: '%s'", i + 2, S.c_str());

        sum[id] += X;
    }

    // Check the problem's global guarantee: answer is YES iff at least
    // one fruit type has total count exactly 5 across all cards.
    int cntExactly5 = 0;
    for (int f = 0; f < 4; ++f)
        if (sum[f] == 5)
            ++cntExactly5;

    // The problem statement does not restrict how many fruit types
    // can have exactly 5 in total; it just says "one or more kinds".
    // So there's no extra structural constraint beyond that the
    // computed answer is well-defined (which it always is).
    // No further global checks are necessary.

    inf.readEof();
}
