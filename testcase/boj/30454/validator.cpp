#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int L = inf.readInt(1, 1000, "L");
    inf.readEoln();

    // Read N binary strings
    for (int i = 0; i < N; i++) {
        // Read the string token consisting of 0/1
        string s = inf.readToken("[01]+", "s_" + to_string(i+1));
        // Check exact length L
        ensuref((int)s.length() == L,
                "Length of s_%d is %d but expected %d", i+1, (int)s.length(), L);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
