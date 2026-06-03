#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int s = inf.readInt(1, n, "S");
    inf.readSpace();
    int d = inf.readInt(1, n, "D");
    inf.readSpace();
    int f = inf.readInt(0, 100000, "F");
    inf.readSpace();
    int b = inf.readInt(0, 100000, "B");
    inf.readSpace();
    int k = inf.readInt(0, n / 2, "K");
    inf.readEoln();

    ensuref(s != d, "S and D must be different: %d", s);

    if (k > 0) {
        set<int> policeStations;
        for (int i = 1; i <= k; ++i) {
            int police = inf.readInt(1, n, "l_i");
            // CHECK: The statement writes S != D != l; interpret police stations
            // as distinct from both the starting gold shop and destination home.
            ensuref(police != s, "police station %d equals S: %d", i, police);
            ensuref(police != d, "police station %d equals D: %d", i, police);
            ensuref(policeStations.insert(police).second,
                    "duplicate police station at index %d: %d", i, police);

            if (i < k) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
