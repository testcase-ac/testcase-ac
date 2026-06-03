#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        vector<int> seen(n + 1, 0);
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            int gift = inf.readInt(1, n, "gift");
            ensuref(!seen[gift], "cow %d wishlist repeats gift %d", i + 1, gift);
            seen[gift] = 1;
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
