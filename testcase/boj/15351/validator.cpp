#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of entries N: must be between 1 and 100000
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Each of the next N lines: a name consisting of uppercase letters and spaces, length 1..30
    for (int i = 0; i < N; i++) {
        string name = inf.readLine("[A-Z\\ ]{1,30}", "name");
        ensuref(name.front() != ' ', "name %d has leading space", i + 1);
        ensuref(name.back() != ' ', "name %d has trailing space", i + 1);
        ensuref(name.find("  ") == string::npos, "name %d has repeated spaces", i + 1);
    }

    inf.readEof();
    return 0;
}
