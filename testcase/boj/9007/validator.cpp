#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound T. With n <= 1000, T <= 1000 keeps
    // the maximum scalar-token count below the repo's practical cap.
    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int k = inf.readInt(1, 40000000, "k");
        inf.readSpace();
        int n = inf.readInt(1, 1000, "n");
        inf.readEoln();

        for (int classIndex = 1; classIndex <= 4; ++classIndex) {
            vector<int> weights = inf.readInts(n, 1, 10000000, "weight");
            (void)weights;
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
