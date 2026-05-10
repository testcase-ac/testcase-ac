#include "testlib.h"
#include <vector>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int T_MAX = 100000;
    int menuCount = 0;

    while (true) {
        int N = inf.readInt(0, 10, "N");
        inf.readEoln();

        if (N == 0) {
            // End of input
            break;
        }

        ++menuCount;
        ensuref(menuCount <= T_MAX, "Too many menus: %d (max %d)", menuCount, T_MAX);

        vector<int> D(N), P(N);
        for (int i = 0; i < N; ++i) {
            D[i] = inf.readInt(1, 36, "D_i");
            inf.readSpace();
            P[i] = inf.readInt(1, 100, "P_i");
            inf.readEoln();
        }

        // Check that all diameters are distinct
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                ensuref(D[i] != D[j],
                        "Diameters must be distinct within a menu (menu %d, entries %d and %d both have D=%d)",
                        menuCount, i + 1, j + 1, D[i]);
            }
        }

        // Check that all inherent cost per square inch are distinct.
        // Cost per sq inch = P / (pi * (D/2)^2) = 4 * P / (pi * D^2).
        // Distinct inherent cost per square inch <=> for all i != j:
        // P[i] / D[i]^2 != P[j] / D[j]^2  <=>  P[i]*D[j]^2 != P[j]*D[i]^2
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                long long lhs = 1LL * P[i] * D[j] * D[j];
                long long rhs = 1LL * P[j] * D[i] * D[i];
                ensuref(lhs != rhs,
                        "Two pizzas have the same inherent cost per square inch "
                        "(menu %d, entries %d and %d)", menuCount, i + 1, j + 1);
            }
        }

        // Additionally, verify that there is a unique best value pizza as implied.
        // Since costs are distinct, minimum exists and is unique.
        int bestIdx = 0;
        long double bestCost = (long double)P[0] / ((long double)D[0] * (long double)D[0]);
        for (int i = 1; i < N; ++i) {
            long double cost = (long double)P[i] / ((long double)D[i] * (long double)D[i]);
            if (cost < bestCost) {
                bestCost = cost;
                bestIdx = i;
            }
        }
        // No need for extra ensuref here: distinct costs guarantee uniqueness.

    }

    inf.readEof();
}
