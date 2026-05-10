#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // Read n
        int n = inf.readInt(8, 12, "n");
        inf.readSpace();

        // Read sequence
        vector<int> seq = inf.readInts(n, -1000, 1000, "seq");
        inf.readEoln();

        // Global: "처음 d개 숫자는 0이 아니다." for the d of the recurrence
        // But we don't know d yet. So for d=1,2,3, check if a recurrence exists, and for that d, check first d nonzero.
        // However, the problem guarantees: "항상 적어도 하나의 식을 만족하는 수열만 주어지며, 처음 d개 숫자는 0이 아니다."
        // So we must check that for at least one d=1,2,3, there exists integer coefficients a_1..a_d such that
        // for all i in [d, n-1]: seq[i] == a_1*seq[i-1] + ... + a_d*seq[i-d]
        // and seq[0..d-1] != 0

        bool found = false;
        for (int d = 1; d <= 3; ++d) {
            // Check first d elements are nonzero
            bool all_nonzero = true;
            for (int i = 0; i < d; ++i) {
                if (seq[i] == 0) {
                    all_nonzero = false;
                    break;
                }
            }
            if (!all_nonzero) continue;

            // Try to find integer coefficients a_1..a_d
            // For each i in [d, n-1]: seq[i] = a_1*seq[i-1] + ... + a_d*seq[i-d]
            // Set up system: for i = d..n-1, equation:
            // seq[i] = sum_{j=1}^d a_j * seq[i-j]
            // System: M * a = b
            int eqs = n - d;
            if (eqs < d) continue; // Not enough equations to uniquely determine a_1..a_d

            // Build matrix A (d x d), vector y (d)
            vector<vector<long long>> A(d, vector<long long>(d));
            vector<long long> y(d);
            for (int i = 0; i < d; ++i) {
                for (int j = 0; j < d; ++j) {
                    A[i][j] = seq[d + i - j - 1];
                }
                y[i] = seq[d + i];
            }

            // Compute determinant of A
            long long detA = 0;
            if (d == 1) {
                detA = A[0][0];
            } else if (d == 2) {
                detA = A[0][0] * A[1][1] - A[0][1] * A[1][0];
            } else if (d == 3) {
                detA = A[0][0]*A[1][1]*A[2][2] + A[0][1]*A[1][2]*A[2][0] + A[0][2]*A[1][0]*A[2][1]
                     - A[0][2]*A[1][1]*A[2][0] - A[0][0]*A[1][2]*A[2][1] - A[0][1]*A[1][0]*A[2][2];
            }
            if (detA == 0) continue; // Singular, skip

            // Compute determinants for each variable
            vector<long long> coeffs(d);
            bool all_integer = true;
            for (int var = 0; var < d; ++var) {
                vector<vector<long long>> B = A;
                for (int i = 0; i < d; ++i) {
                    B[i][var] = y[i];
                }
                long long detB = 0;
                if (d == 1) {
                    detB = B[0][0];
                } else if (d == 2) {
                    detB = B[0][0] * B[1][1] - B[0][1] * B[1][0];
                } else if (d == 3) {
                    detB = B[0][0]*B[1][1]*B[2][2] + B[0][1]*B[1][2]*B[2][0] + B[0][2]*B[1][0]*B[2][1]
                         - B[0][2]*B[1][1]*B[2][0] - B[0][0]*B[1][2]*B[2][1] - B[0][1]*B[1][0]*B[2][2];
                }
                if (detB % detA != 0) {
                    all_integer = false;
                    break;
                }
                coeffs[var] = detB / detA;
            }
            if (!all_integer) continue;

            // Now check all equations (not just first d)
            bool valid = true;
            for (int i = d; i < n; ++i) {
                long long val = 0;
                for (int j = 0; j < d; ++j) {
                    val += coeffs[j] * seq[i - j - 1];
                }
                if (val != seq[i]) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                found = true;
                break;
            }
        }
        ensuref(found, "No valid recurrence of order 1,2,3 found for test case %d", tc + 1);
    }

    inf.readEof();
}
