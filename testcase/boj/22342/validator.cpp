#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N
    int M = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int N = inf.readInt(1, 2000, "N");
    inf.readEoln();

    // Read M lines, each with exactly N digits, each digit in [1,9]
    for (int i = 1; i <= M; ++i) {
        string line = inf.readLine("[1-9]{1,2000}", "weights_row");
        ensuref((int)line.size() == N, "Row %d: Expected %d digits, got %d", i, N, (int)line.size());
        // No spaces allowed, only digits 1-9
    }

    inf.readEof();
}
