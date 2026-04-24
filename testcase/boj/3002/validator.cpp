#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read the initial dial string: exactly N digits [0-9]
    string regex_digits = "[0-9]{" + to_string(N) + "," + to_string(N) + "}";
    inf.readLine(regex_digits.c_str(), "initial");

    // Read M queries
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readEoln();
        ensuref(A <= B,
                "Query %d has invalid range: A (%d) > B (%d)",
                i + 1, A, B);
    }

    inf.readEof();
    return 0;
}
