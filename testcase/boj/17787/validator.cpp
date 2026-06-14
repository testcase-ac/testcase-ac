#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 1000, "k");
    inf.readEoln();

    long long totalN = 0;
    for (int photo = 1; photo <= k; ++photo) {
        setTestCase(photo);

        int n = inf.readInt(3, 300000, "n");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 300000, "total number of people exceeds 300000");

        set<int> heights;
        for (int i = 1; i <= n; ++i) {
            int h = inf.readInt(1, 1000000000, "h_i");
            ensuref(heights.insert(h).second,
                    "duplicate height in photo %d at position %d: %d",
                    photo, i, h);

            if (i == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
