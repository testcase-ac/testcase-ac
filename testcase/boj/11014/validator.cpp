#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int C = inf.readInt(1, 100000, "C");
    inf.readEoln();

    for (int tc = 1; tc <= C; tc++) {
        setTestCase(tc);

        // Read N and M
        int N = inf.readInt(1, 80, "N");
        inf.readSpace();
        int M = inf.readInt(1, 80, "M");
        inf.readEoln();

        // Read the classroom grid
        for (int i = 1; i <= N; i++) {
            // Read a line of length between 1 and 80, then check it equals M
            string row = inf.readLine("[.x]{1,80}", "row");
            ensuref((int)row.size() == M,
                    "In test case %d, row %d has length %d but expected %d",
                    tc, i, (int)row.size(), M);
            // Characters are already guaranteed to be '.' or 'x' by the regex
        }
    }

    inf.readEof();
    return 0;
}
