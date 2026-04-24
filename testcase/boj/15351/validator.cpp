#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of entries N: must be between 1 and 100000
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Each of the next N lines: a name consisting of uppercase letters and spaces, length 1..30
    // Regex: [A-Z\ ] matches uppercase or space; space must be escaped
    for (int i = 0; i < N; i++) {
        inf.readLine("[A-Z\\ ]{1,30}", "name");
    }

    inf.readEof();
    return 0;
}
