#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read target channel N
    int N = inf.readInt(0, 500000, "N");
    inf.readEoln();

    // Read number of broken buttons M
    int M = inf.readInt(0, 10, "M");
    inf.readEoln();

    // If there are broken buttons, read them and ensure they are distinct
    if (M > 0) {
        vector<int> broken = inf.readInts(M, 0, 9, "broken_i");
        inf.readEoln();

        bool seen[10] = {false};
        for (int i = 0; i < M; i++) {
            int x = broken[i];
            ensuref(!seen[x],
                    "Broken button %d is specified multiple times", x);
            seen[x] = true;
        }
    }

    inf.readEof();
    return 0;
}
