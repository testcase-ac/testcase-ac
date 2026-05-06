#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int C = inf.readInt(1, 100000, "C");
    inf.readEoln();

    for (int tc = 1; tc <= C; tc++) {
        setTestCase(tc);

        // Read N and M
        int N = inf.readInt(1, 10, "N");
        inf.readSpace();
        int M = inf.readInt(1, 10, "M");
        inf.readEoln();

        // Read the classroom layout
        for (int i = 0; i < N; i++) {
            // Each row must be exactly M characters of '.' or 'x'
            string row = inf.readToken("[.x]+", "row");
            ensuref((int)row.length() == M,
                    "In test case %d, row %d has length %d but expected %d",
                    tc, i+1, row.length(), M);
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
