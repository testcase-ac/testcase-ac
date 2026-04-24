#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int C = inf.readInt(1, 100, "C");
    inf.readEoln();

    // Allowed complexities regex
    const char* comp_regex = "O\\(N\\)|O\\(N\\^2\\)|O\\(N\\^3\\)|O\\(2\\^N\\)|O\\(N!\\)";

    for (int i = 0; i < C; i++) {
        // Read complexity string S
        inf.readToken(comp_regex, "S");
        inf.readSpace();

        // Read N, T, L with their constraints
        int N = inf.readInt(1, 1000000, "N");
        inf.readSpace();

        int T = inf.readInt(1, 10, "T");
        inf.readSpace();

        int L = inf.readInt(1, 10, "L");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
