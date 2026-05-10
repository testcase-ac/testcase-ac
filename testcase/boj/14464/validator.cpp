#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read C and N
    int C = inf.readInt(1, 20000, "C");
    inf.readSpace();
    int N = inf.readInt(1, 20000, "N");
    inf.readEoln();

    // 2. Read C lines: T_1 ... T_C
    vector<int> T(C);
    for (int i = 0; i < C; ++i) {
        T[i] = inf.readInt(0, 1000000000, "T_i");
        inf.readEoln();
    }

    // 3. Read N lines: A_j B_j
    vector<pair<int,int>> cows(N);
    for (int j = 0; j < N; ++j) {
        int A = inf.readInt(0, 1000000000, "A_j");
        inf.readSpace();
        int B = inf.readInt(A, 1000000000, "B_j");
        inf.readEoln();
        cows[j] = make_pair(A, B);
    }

    // 4. Global property: For the given input, the answer always exists? 
    // No such guarantee in the statement. No need to check for matching existence.
    // No further global property to check.

    // 5. Formatting: EOF
    inf.readEof();
}
