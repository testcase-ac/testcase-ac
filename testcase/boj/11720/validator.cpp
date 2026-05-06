#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of digits
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read the line containing exactly N digits (no spaces)
    string s = inf.readLine("[0-9]+", "digits");
    ensuref((int)s.size() == N,
            "Length of digits string (%d) does not match N (%d)", (int)s.size(), N);

    // No extra characters after the final newline
    inf.readEof();
    return 0;
}
