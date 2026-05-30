#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K
    int N = inf.readInt(3, 10000, "N");
    inf.readSpace();
    int K = inf.readInt(3, 1000, "K");
    inf.readEoln();

    vector<double> residues;
    residues.reserve(N);
    const double sector = 360.0 / K;
    const double eps = 1e-9;

    for (int i = 0; i < N; i++) {
        double ang = inf.readDouble(0.0, 360.0, "angle");
        ensuref(ang < 360.0,
                "angle at index %d is %.10f but must be strictly less than 360",
                i + 1, ang);
        inf.readEoln();

        double residue = fmod(ang, sector);
        if (residue < 0) {
            residue += sector;
        }
        residues.push_back(residue);
    }

    sort(residues.begin(), residues.end());
    for (int i = 1; i < N; ++i) {
        ensuref(residues[i] - residues[i - 1] > eps,
                "angles at indices modulo sector width are too close");
    }
    ensuref((residues.front() + sector) - residues.back() > eps,
            "angles at indices modulo sector width are too close across wrap");

    inf.readEof();
    return 0;
}
