#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 26, "N");
    inf.readSpace();
    int M = inf.readInt(1, 20000, "M");
    inf.readEoln();

    // Read M strings
    for (int i = 0; i < M; i++) {
        // Must be exactly N uppercase letters
        string str = inf.readToken("[A-Z]+", "str");
        ensuref((int)str.length() == N,
                "String at line %d has length %d, but expected %d", 
                i + 2, (int)str.length(), N);
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
