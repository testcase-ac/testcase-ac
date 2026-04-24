#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(0, 10, "N");
    inf.readSpace();
    int M = inf.readInt(0, 10, "M");
    inf.readEoln();

    // Read N rows of length M, each character must be '0' or '1'
    for (int i = 0; i < N; i++) {
        string row = inf.readLine("[01]*", "row");
        ensuref((int)row.size() == M,
                "Row %d: expected length %d, found %d",
                i + 1, M, (int)row.size());
        // The regex guarantees only '0' or '1' characters
    }

    inf.readEof();
    return 0;
}
