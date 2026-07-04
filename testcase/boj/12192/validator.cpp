#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int N = inf.readInt(1, 10, "N");
        inf.readEoln();

        vector<int> stationCounts(N);
        int totalStations = 0;
        for (int i = 0; i < N; ++i) {
            stationCounts[i] = inf.readInt(2, 100, "SN_i");
            inf.readSpace();
            inf.readInt(1, 100, "W_i");
            inf.readEoln();

            totalStations += stationCounts[i];
            ensuref(totalStations <= 100,
                    "total number of stations exceeds 100 after line %d", i + 1);

            for (int j = 0; j < stationCounts[i] - 1; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readInt(1, 100, "Time_i_j");
            }
            inf.readEoln();
        }

        int M = inf.readInt(0, 10, "M");
        inf.readEoln();
        for (int i = 0; i < M; ++i) {
            int m1 = inf.readInt(1, N, "m1_i");
            inf.readSpace();
            int s1 = inf.readInt(1, stationCounts[m1 - 1], "s1_i");
            inf.readSpace();
            int m2 = inf.readInt(1, N, "m2_i");
            inf.readSpace();
            int s2 = inf.readInt(1, stationCounts[m2 - 1], "s2_i");
            inf.readSpace();
            inf.readInt(1, 100, "t_i");
            inf.readEoln();

            ensuref(m1 != m2, "tunnel %d connects stations on the same line %d",
                    i + 1, m1);
            (void)s1;
            (void)s2;
        }

        int Q = inf.readInt(1, 10, "Q");
        inf.readEoln();
        for (int i = 0; i < Q; ++i) {
            int x1 = inf.readInt(1, N, "x1");
            inf.readSpace();
            int y1 = inf.readInt(1, stationCounts[x1 - 1], "y1");
            inf.readSpace();
            int x2 = inf.readInt(1, N, "x2");
            inf.readSpace();
            int y2 = inf.readInt(1, stationCounts[x2 - 1], "y2");
            inf.readEoln();

            ensuref(x1 != x2 || y1 != y2,
                    "query %d has identical source and destination station", i + 1);
        }
    }

    inf.readEof();
}
