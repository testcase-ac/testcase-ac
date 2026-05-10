#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_CASES = 100000;
    int test_cases = 0;
    while (!inf.seekEof()) {
        ++test_cases;
        ensuref(test_cases <= MAX_CASES, "Number of test cases exceeds %d", MAX_CASES);

        // Read X_dest and L
        double X_dest = inf.readDouble(1.0, 10000.0, "X_dest");
        inf.readSpace();
        int L = inf.readInt(0, 10, "L");
        inf.readEoln();

        vector<double> Xs;
        for (int i = 0; i < L; ++i) {
            double X_i = inf.readDouble(0.0, X_dest, "X_i");
            inf.readSpace();
            double R_i = inf.readDouble(10.0, 500.0, "R_i");
            inf.readSpace();
            double G_i = inf.readDouble(10.0, 500.0, "G_i");
            inf.readEoln();

            ensuref(X_i > 0.0 && X_i < X_dest, 
                "Signal position X_i=%.10f must satisfy 0 < X_i < X_dest=%.10f (test case %d, signal %d)", 
                X_i, X_dest, test_cases, i+1);

            Xs.push_back(X_i);
        }

        // Check that Xs are strictly increasing and no duplicates
        for (int i = 1; i < L; ++i) {
            ensuref(Xs[i] > Xs[i-1], 
                "Signal positions must be strictly increasing: X_%d=%.10f, X_%d=%.10f (test case %d)", 
                i, Xs[i-1], i+1, Xs[i], test_cases);
        }
    }

    inf.readEof();
}
