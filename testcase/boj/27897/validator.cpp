#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000000000000LL, "L");
    inf.readEoln();

    vector<bool> seen(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int student = inf.readInt(1, n, "student_i");
        ensuref(!seen[student], "duplicate student number at position %d: %d", i, student);
        seen[student] = true;
    }
    inf.readEoln();

    inf.readEof();
}
