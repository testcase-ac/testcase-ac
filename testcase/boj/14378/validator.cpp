#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 50, "N");
        inf.readEoln();

        vector<int> parity(2501, 0);
        for (int i = 0; i < 2 * n - 1; ++i) {
            int previous = 0;
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                int height = inf.readInt(1, 2500, "height");
                ensuref(height > previous,
                        "list %d is not strictly increasing at position %d: %d after %d",
                        i + 1, j + 1, height, previous);
                parity[height] ^= 1;
                previous = height;
            }
            inf.readEoln();
        }

        vector<int> missing;
        for (int height = 1; height <= 2500; ++height) {
            if (parity[height]) {
                missing.push_back(height);
            }
        }
        ensuref((int)missing.size() == n,
                "parity-derived missing list has size %d, expected %d",
                (int)missing.size(), n);
    }

    inf.readEof();
}
