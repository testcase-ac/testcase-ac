#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

/*
Problem:
- N persons and N jobs (1..N).
- Cost matrix D (N x N), D_ij: cost when person i does job j.
- 1 <= N <= 500.
- Costs are natural numbers (positive integers) <= 10000.
- Goal (for solution) is to find minimal total cost assignment.

As validator:
- Check:
  * N in [1, 500], canonical integer.
  * Exactly N lines follow.
  * Each of these lines has exactly N integers.
  * Each cost in [1, 10000], canonical.
  * Whitespace is strict.
  * EOF right after last newline.

No extra global properties are implied (e.g., no promise about existence
of solution beyond trivial: all costs are positive and matrix is complete).
So no need to run Hungarian or similar in validator.
*/

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        // Read exactly N integers on this line
        for (int j = 0; j < N; ++j) {
            int val = inf.readInt(1, 10000, "D_ij");
            if (j + 1 < N)
                inf.readSpace();
        }
        inf.readEoln();
    }

    inf.readEof();
}
