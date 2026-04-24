#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of lines N: must be between 1 and 100000
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read exactly N lines, each up to 50 characters (any characters except newline)
    for (int i = 0; i < N; i++) {
        // [^] matches any character except newline; {0,50} ensures length ≤ 50
        inf.readLine("[^]{0,50}", "line");
    }

    inf.readEof();
    return 0;
}
