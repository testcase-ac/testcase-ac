#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of islands
    int N = inf.readInt(3, 500, "N");
    inf.readEoln();

    vector<int> dist(N), strength(N), usable(N);
    for (int i = 0; i < N; i++) {
        // Distance from Yusi island
        dist[i] = inf.readInt(0, 100000, "dist");
        inf.readSpace();
        // Spring strength
        strength[i] = inf.readInt(1, 1000, "strength");
        inf.readSpace();
        // Usable with princess?
        usable[i] = inf.readInt(0, 1, "usable");
        inf.readEoln();

        if (i == 0) {
            ensuref(dist[i] == 0,
                    "First island must have distance 0, found dist[0]=%d",
                    dist[i]);
        }
        if (i > 0) {
            ensuref(dist[i] > dist[i - 1],
                    "Distances must be strictly increasing: dist[%d]=%d >= dist[%d]=%d",
                    i - 1, dist[i - 1], i, dist[i]);
        }
        if (i == N - 1) {
            ensuref(usable[i] == 1,
                    "Last island (Hooper) must have usable=1, found usable[%d]=%d",
                    i, usable[i]);
        }
    }

    inf.readEof();
    return 0;
}
