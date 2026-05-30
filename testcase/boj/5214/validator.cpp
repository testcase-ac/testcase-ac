#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 0; i < M; i++) {
        set<int> stations;
        for (int j = 0; j < K; j++) {
            int x = inf.readInt(1, N, "station");
            // CHECK: "K stations" implies distinct station labels in one hypertube.
            ensuref(stations.insert(x).second,
                    "duplicate station %d in hypertube %d", x, i + 1);
            if (j + 1 < K) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
    return 0;
}
