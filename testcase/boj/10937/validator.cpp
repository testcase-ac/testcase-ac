#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 11, "N");
    inf.readEoln();

    // Read each of the N rows, ensure exactly N characters in {A,B,C,F}
    for (int i = 0; i < N; i++) {
        // Build regex for exactly N characters from the set {A,B,C,F}
        string regex = string("[ABCF]{") + to_string(N) + "," + to_string(N) + "}";
        inf.readToken(regex.c_str(), "row");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
