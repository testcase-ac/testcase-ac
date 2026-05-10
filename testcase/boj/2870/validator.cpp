#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of lines
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each of the next N lines: only lowercase letters and digits, length up to 100
    for (int i = 0; i < N; i++) {
        inf.readLine("[a-z0-9]{0,100}", "line");
    }

    inf.readEof();
    return 0;
}
