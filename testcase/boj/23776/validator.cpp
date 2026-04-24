#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of waypoints
    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    // Read waypoints
    vector<int> phi(n), lambda(n);
    for (int i = 0; i < n; i++) {
        phi[i] = inf.readInt(-89, 89, "phi");
        inf.readSpace();
        lambda[i] = inf.readInt(-180, 179, "lambda");
        inf.readEoln();
    }

    // Check no two consecutive waypoints (including last->first) are equal or antipodal
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        // Equal check
        ensuref(!(phi[i] == phi[j] && lambda[i] == lambda[j]),
                "Waypoints %d and %d are equal: (%d, %d)",
                i+1, j+1, phi[i], lambda[i]);
        // Antipodal check: latitudes sum to 0 and longitudes differ by 180 modulo 360
        bool lat_opposite = (phi[i] + phi[j] == 0);
        int diff = lambda[i] - lambda[j];
        bool lon_opposite = (abs(diff) == 180);
        ensuref(!(lat_opposite && lon_opposite),
                "Waypoints %d and %d are antipodal: (%d, %d) and (%d, %d)",
                i+1, j+1, phi[i], lambda[i], phi[j], lambda[j]);
    }

    inf.readEof();
    return 0;
}
