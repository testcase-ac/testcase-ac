#include "testlib.h"

#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readEoln();

        vector<int> station_count(n + 1);
        int total_stations = 0;
        for (int i = 1; i <= n; ++i) {
            int sn = inf.readInt(2, 1000, "SN_i");
            inf.readSpace();
            inf.readInt(1, 100, "W_i");
            inf.readEoln();

            inf.readInts(sn - 1, 1, 100, "Time_i_j");
            inf.readEoln();

            station_count[i] = sn;
            total_stations += sn;
            ensuref(total_stations <= 1000,
                    "case %d has too many total stations: %d", tc, total_stations);
        }

        int m = inf.readInt(0, 100, "M");
        inf.readEoln();
        for (int i = 1; i <= m; ++i) {
            int m1 = inf.readInt(1, n, "m1_i");
            inf.readSpace();
            int s1 = inf.readInt(1, station_count[m1], "s1_i");
            inf.readSpace();
            int m2 = inf.readInt(1, n, "m2_i");
            inf.readSpace();
            int s2 = inf.readInt(1, station_count[m2], "s2_i");
            inf.readSpace();
            inf.readInt(1, 100, "t_i");
            inf.readEoln();

            ensuref(m1 != m2, "tunnel %d connects the same metro line %d", i, m1);
            (void)s1;
            (void)s2;
        }

        int q = inf.readInt(1, 10, "Q");
        inf.readEoln();
        for (int i = 1; i <= q; ++i) {
            int x1 = inf.readInt(1, n, "x1");
            inf.readSpace();
            int y1 = inf.readInt(1, station_count[x1], "y1");
            inf.readSpace();
            int x2 = inf.readInt(1, n, "x2");
            inf.readSpace();
            int y2 = inf.readInt(1, station_count[x2], "y2");
            inf.readEoln();

            ensuref(x1 != x2 || y1 != y2,
                    "query %d starts and ends at the same station (%d, %d)", i, x1, y1);
        }
    }

    inf.readEof();
}
