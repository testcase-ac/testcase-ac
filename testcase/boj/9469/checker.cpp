#include "testlib.h"
#include <cmath>
#include <string>

using namespace std;

const double EPS = 1e-2;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int case_no = 0;
    // Compare each line: case number and the computed distance
    while (!ans.seekEof()) {
        case_no++;
        // Read jury's correct output
        int jN = ans.readInt();
        double jVal = ans.readDouble();
        // Read participant's output
        int pN = ouf.readInt();
        if (pN != jN) {
            quitf(_wa, "case %d: expected test case number %d, found %d", case_no, jN, pN);
        }
        double pVal = ouf.readDouble();
        // Compare with allowed absolute error EPS
        if (!doubleCompare(pVal, jVal, EPS)) {
            double diff = fabs(pVal - jVal);
            quitf(_wa,
                  "case %d: value mismatch - expected '%.6f', found '%.6f', abs error = '%.6f'",
                  case_no, jVal, pVal, diff);
        }
    }
    // Ensure no extra output
    if (!ouf.seekEof()) {
        quitf(_wa, "extra output after %d cases", case_no);
    }
    quitf(_ok, "All %d cases are correct.", case_no);
    return 0;
}
