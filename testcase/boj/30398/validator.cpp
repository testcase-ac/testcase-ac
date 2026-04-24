#include "testlib.h"
#include <vector>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: N, d, P
    int N = inf.readInt(2, 1000000, "N"); // N >= 2, max 1e6 (since N * d <= 1e6)
    inf.readSpace();
    int d = inf.readInt(1, 1000000, "d");  // d >= 1, max 1e6
    inf.readSpace();
    int P = inf.readInt(0, 1000, "P");     // P between 0 and 1000
    inf.readEoln();

    // Check product constraints
    ensuref((long long)N * d <= 1000000LL,
            "Constraint violated: N * d = %d * %d = %lld > 1e6", 
            N, d, (long long)N * d);
    ensuref((long long)d * P <= 1000000LL,
            "Constraint violated: d * P = %d * %d = %lld > 1e6",
            d, P, (long long)d * P);

    vector<int> prev;
    vector<int> point(d);
    vector<int> start(d, 1), goal(d, N);

    for (int i = 0; i < P; i++) {
        // Read one point of dimension d
        for (int j = 0; j < d; j++) {
            char nameBuf[50];
            sprintf(nameBuf, "q_%d_%d", i+1, j+1);
            point[j] = inf.readInt(1, N, nameBuf);
            if (j + 1 < d)
                inf.readSpace();
        }
        inf.readEoln();

        // Check sortedness with previous point
        if (i > 0) {
            for (int j = 0; j < d; j++) {
                ensuref(prev[j] <= point[j],
                        "Points not non-decreasing at index %d->%d, dimension %d: %d > %d",
                        i, i+1, j+1, prev[j], point[j]);
            }
            // Check no duplicate of previous
            bool all_equal = true;
            for (int j = 0; j < d; j++) {
                if (prev[j] != point[j]) {
                    all_equal = false;
                    break;
                }
            }
            ensuref(!all_equal,
                    "Duplicate point detected at indices %d and %d", i, i+1);
        }

        // Check not equal to start (all ones)
        {
            bool is_start = true;
            for (int j = 0; j < d; j++)
                if (point[j] != start[j]) { is_start = false; break; }
            ensuref(!is_start,
                    "Point %d coincides with the start (all ones)", i+1);
        }
        // Check not equal to goal (all N)
        {
            bool is_goal = true;
            for (int j = 0; j < d; j++)
                if (point[j] != goal[j]) { is_goal = false; break; }
            ensuref(!is_goal,
                    "Point %d coincides with the goal (all N's)", i+1);
        }

        // Save as previous for next iteration
        prev = point;
    }

    inf.readEof();
    return 0;
}
