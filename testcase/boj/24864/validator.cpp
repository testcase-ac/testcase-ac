#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single-line input: N M
    // Constraints: 1 ≤ N, M ≤ 1e5
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // No multiple test cases, file must end immediately.
    inf.readEof();
}
