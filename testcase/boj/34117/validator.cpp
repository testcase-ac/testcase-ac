#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and P
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int P = inf.readInt(1, 1000000000, "P");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 1000000000, "A_i");
    inf.readEoln();

    // Subtasks
    // 1. N <= 8
    // 2. N <= 5000
    // 3. all A_i == 1
    // 4. all A_i == 2 or 3
    // 5. all A_i <= 50
    // 6. A_i non-decreasing

    // Check for subtask 3: all A_i == 1
    bool all_one = true;
    for (int i = 0; i < N; ++i) {
        if (A[i] != 1) {
            all_one = false;
            break;
        }
    }
    // Check for subtask 4: all A_i == 2 or 3
    bool all_two_three = true;
    for (int i = 0; i < N; ++i) {
        if (A[i] != 2 && A[i] != 3) {
            all_two_three = false;
            break;
        }
    }
    // Check for subtask 5: all A_i <= 50
    bool all_leq_50 = true;
    for (int i = 0; i < N; ++i) {
        if (A[i] > 50) {
            all_leq_50 = false;
            break;
        }
    }
    // Check for subtask 6: non-decreasing
    bool non_decreasing = true;
    for (int i = 1; i < N; ++i) {
        if (A[i-1] > A[i]) {
            non_decreasing = false;
            break;
        }
    }

    // For subtasks, we do not need to enforce any, just check that input is valid for all.

    // No further global constraints to check.

    inf.readEof();
}
