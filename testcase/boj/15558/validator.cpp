#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and k
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "k");
    inf.readEoln();

    // 2. Read left line
    string left = inf.readLine("[01]{1,100000}", "left");
    ensuref((int)left.size() == N, "Left line length mismatch: expected %d, got %d", N, (int)left.size());

    // 3. Read right line
    string right = inf.readLine("[01]{1,100000}", "right");
    ensuref((int)right.size() == N, "Right line length mismatch: expected %d, got %d", N, (int)right.size());

    // 4. Check left[0] == '1'
    ensuref(left[0] == '1', "The first cell of the left line (left[1]) must be safe (1), but got %c", left[0]);

    // 5. No extra lines
    inf.readEof();
}
