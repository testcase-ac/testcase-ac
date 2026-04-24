#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read binary string A
    // According to the problem, in actual tests both A and B have length exactly 100000.
    // However, sample tests (which are not judged) may have shorter lengths (e.g., 10).
    // Therefore we allow lengths from 1 to 100000, and enforce A and B to have the same length.
    string A = inf.readLine("[01]{1,100000}", "A");
    string B = inf.readLine("[01]{1,100000}", "B");

    // Enforce that A and B have the same length
    ensuref((int)A.size() == (int)B.size(),
            "Lengths of A and B must be equal, found %d and %d", (int)A.size(), (int)B.size());

    // Optionally, one could enforce that in real tests the length is 100000:
    // ensuref((int)A.size() == 100000, "Length of A must be exactly 100000, found %d", (int)A.size());
    // But to allow sample cases to pass validation, we do not enforce this here.

    inf.readEof();
    return 0;
}
